/*
 * i2clcd.c
 *
 * Minimal library to drive LCD displays with i2c
 *
 * Copyright (c) 2022 Lars Boegild Thomsen <lbthomsen@gmail.com>
 *
 * License is LICENSE file.
 *
 */

#include "main.h"
#include "i2clcd.h"

static uint32_t i2c_1_us_cycles;

/*
 *
 * Internal functions
 *
 */

/**
 * @brief  A rather silly function to introduce a brief us range delay.  It is not meant
 *         to be precise in anyway just leave enough time to make a signal settle.  The
 *         value of i2c_1_us_cycles is determined at initialization based on actual clock
 *         frequency / 2 million (assuming the loop does at least 2 instructions).
 *         Using a timer would be better, but probably not worth tying one up just for this.
 * @param  Very approximate time in us.  The actual time will be quite a lot longer - probably more
 *         than double.
 * @retval none
 */
void i2clcd_delay_us(uint32_t us) {
	for (uint32_t l = 0; l < us; ++l) {
		for (uint32_t i = 0; i < i2c_1_us_cycles; ++i) { // This should take approximately 1 us
			asm("NOP");
		}
	}
}

I2CLcd_result_t i2clcd_write(I2CLcd_HandleTypeDef *i2clcd, uint8_t data) {
	I2CLcd_result_t result = I2CLcd_OK;
	uint8_t write_data = data | i2clcd->backlight;
	HAL_StatusTypeDef ret = HAL_I2C_Master_Transmit(i2clcd->i2c, i2clcd->address << 1, (uint8_t *)&write_data, 1, HAL_MAX_DELAY);
	if (ret != HAL_OK) {
		result = I2CLcd_Err;
	}
	return result;
}

I2CLcd_result_t i2clcd_pulse(I2CLcd_HandleTypeDef *i2clcd, uint8_t data) {
	I2CLcd_result_t result = I2CLcd_OK;
	result = i2clcd_write(i2clcd, data | LCD_EN);
	i2clcd_delay_us(1);
	result = i2clcd_write(i2clcd, data & ~LCD_EN);
	i2clcd_delay_us(1);
	return result;
}

I2CLcd_result_t i2clcd_write4bits(I2CLcd_HandleTypeDef *i2clcd, uint8_t data) {
	I2CLcd_result_t result = I2CLcd_OK;
	result = i2clcd_pulse(i2clcd, data);
	return result;
}

I2CLcd_result_t i2clcd_send(I2CLcd_HandleTypeDef *i2clcd, uint8_t data, uint8_t mode) {
	I2CLcd_result_t result = I2CLcd_OK;
	uint8_t highnib =data & 0xf0;
	uint8_t lownib = (data << 4) & 0xf0;
	result = i2clcd_write4bits(i2clcd, (highnib) | mode);
	result = i2clcd_write4bits(i2clcd, (lownib) | mode);
	return result;
}

I2CLcd_result_t i2clcd_command(I2CLcd_HandleTypeDef *i2clcd, uint8_t data) {
	return i2clcd_send(i2clcd, data, 0);
}

I2CLcd_result_t i2clcd_data(I2CLcd_HandleTypeDef *i2clcd, uint8_t data) {
	return i2clcd_send(i2clcd, data, LCD_RS);
}

/*
 *
 * Public functions
 *
 */


I2CLcd_result_t i2clcd_init(I2CLcd_HandleTypeDef *i2clcd, I2C_HandleTypeDef *i2c, uint8_t address) {
	I2CLcd_result_t result = I2CLcd_OK;
	i2clcd->i2c = i2c;
	i2clcd->address = address;

	i2clcd->displayfunction = LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS;
	i2clcd->backlight = LCD_BACKLIGHT;

	i2c_1_us_cycles = HAL_RCC_GetSysClockFreq() / 2000000;

	HAL_Delay(50);

	i2clcd_write(i2clcd, i2clcd->backlight);

	HAL_Delay(1000);

	i2clcd_write4bits(i2clcd, 0x03 << 4);
	HAL_Delay(4);
	i2clcd_write4bits(i2clcd, 0x03 << 4);
	HAL_Delay(4);
	i2clcd_write4bits(i2clcd, 0x03 << 4);
	HAL_Delay(4);

	i2clcd_command(i2clcd, i2clcd->displayfunction | LCD_CURSORON);

	i2clcd_write4bits(i2clcd, 0x02 << 4);

	i2clcd_delay_us(1);

	return result;
}

I2CLcd_result_t i2clcd_set_backlight(I2CLcd_HandleTypeDef *i2clcd, uint8_t backlight) {
	if (backlight) i2clcd->backlight = LCD_BACKLIGHT;
	else i2clcd->backlight = LCD_NOBACKLIGHT;
	return i2clcd_write(i2clcd, i2clcd->backlight);
}
