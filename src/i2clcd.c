/*
 * i2clcd.c
 *
 *  Created on: May 25, 2022
 *      Author: lth
 */

#include "main.h"
#include "i2clcd.h"

I2CLcd_result_t i2clcd_init(I2CLcd_HandleTypeDef *i2clcd, I2C_HandleTypeDef *i2c) {
	I2CLcd_result_t result = I2CLcd_OK;
	i2clcd->i2c = i2c;

	for (uint8_t i = 0; i < 128; i++) {

	  if (HAL_I2C_IsDeviceReady(i2clcd->i2c, (uint16_t)(i<<1), 3, 5) == HAL_OK) {
		  // We got an ack
		  printf("%2x ", i);
	  } else {
		  printf("-- ");
	  }

	  if (i > 0 && (i + 1) % 16 == 0) printf("\n");

	}

	printf("\n");


	return result;
}
