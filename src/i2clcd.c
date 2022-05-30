/*
 * i2clcd.c
 *
 *  Created on: May 25, 2022
 *      Author: lth
 */

#include "main.h"
#include "i2clcd.h"

I2CLcd_result_t i2clcd_init(I2CLcd_HandleTypeDef *i2clcd, I2C_HandleTypeDef *i2c, uint8_t address) {
	I2CLcd_result_t result = I2CLcd_OK;
	i2clcd->i2c = i2c;
	i2clcd->address = address;
	return result;
}
