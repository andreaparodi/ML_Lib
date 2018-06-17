/*
 * gpio.c
 *
 *  Created on: 08 giu 2018
 *      Author: andre
 */
#include "gpio.h"

void gpioInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__GPIOB_CLK_ENABLE();
	/* Configure the GPIO_LED pin */
	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void HAL_GPIO_EXTI_Callback(uint16_t gpioPin)
{
	if(gpioPin == GPIO_PIN_0)
	{
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_5);
	}
}

