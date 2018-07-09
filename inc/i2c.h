/*
 * i2c.h
 *      Author: andre
 */

#ifndef I2C_H_
#define I2C_H_

#include "main.h"

#define I2Cx_FORCE_RESET()               __HAL_RCC_I2C1_FORCE_RESET()
#define I2Cx_RELEASE_RESET()             __HAL_RCC_I2C1_RELEASE_RESET()


I2C_HandleTypeDef I2C1Handle;

void I2C1_init(void);
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c);
void Error_Handler();

#endif /* I2C_H_ */
