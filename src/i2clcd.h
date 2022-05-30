/*
 * i2clcd.h
 *
 *  Created on: May 25, 2022
 *      Author: lth
 */

#ifndef I2CLCD_H_
#define I2CLCD_H_

#define LCD_DEFAULT_ADDRESS 0x27

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define LCD_EN 0b00000100  // Enable bit
#define LCD_RW 0b00000010  // Read/Write bit
#define LCD_RS 0b00000001  // Register select bit

typedef struct {
	I2C_HandleTypeDef *i2c;
	uint8_t address;
	uint8_t displayfunction;
	uint8_t displaycontrol;
	uint8_t displaymode;
	uint8_t cols;
	uint8_t rows;
	uint8_t charsize;
	uint8_t backlight;
} I2CLcd_HandleTypeDef;

typedef enum {
	I2CLcd_OK,
	I2CLcd_Err,
	I2CLcd_Timeout
} I2CLcd_result_t;

I2CLcd_result_t i2clcd_init(I2CLcd_HandleTypeDef *i2clcd, I2C_HandleTypeDef *i2c, uint8_t address);

#endif /* I2CLCD_H_ */
