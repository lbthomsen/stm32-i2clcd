/*
 * i2clcd.h
 *
 *  Created on: May 25, 2022
 *      Author: lth
 */

#ifndef I2CLCD_H_
#define I2CLCD_H_

typedef struct {
	I2C_HandleTypeDef *i2c;
} I2CLcd_HandleTypeDef;

typedef enum {
	I2CLcd_OK,
	I2CLcd_Err
} I2CLcd_result_t;

I2CLcd_result_t i2clcd_init(I2CLcd_HandleTypeDef *i2clcd, I2C_HandleTypeDef *i2c);

#endif /* I2CLCD_H_ */
