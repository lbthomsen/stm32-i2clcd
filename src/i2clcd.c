/*
 * i2clcd.c
 *
 *  Created on: May 25, 2022
 *      Author: lth
 */

#include "main.h"
#include "i2clcd.h"

I2CLcd_result_t i2clcd_write(I2CLcd_HandleTypeDef *i2clcd, uint8_t data) {
	I2CLcd_result_t result = I2CLcd_OK;
	HAL_StatusTypeDef ret = HAL_I2C_Master_Transmit(i2clcd->i2c, i2clcd->address << 1, (uint8_t *)&data, 1, HAL_MAX_DELAY);
	if (ret != HAL_OK) {
		result = I2CLcd_Err;
	}
	return result;
}

I2CLcd_result_t i2clcd_init(I2CLcd_HandleTypeDef *i2clcd, I2C_HandleTypeDef *i2c, uint8_t address) {
	I2CLcd_result_t result = I2CLcd_OK;
	i2clcd->i2c = i2c;
	i2clcd->address = address;

	i2clcd->displayfunction = LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS;
	i2clcd->backlight = LCD_BACKLIGHT;

	HAL_Delay(50);

	i2clcd_write(i2clcd, i2clcd->backlight);

	HAL_Delay(1000);



	return result;
}
