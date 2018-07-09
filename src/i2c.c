/*
 * i2c.c
 *      Author: andre
 */
#include "i2c.h"

void I2C1_init(void)
{
	/*##-1- Configure the I2C peripheral ######################################*/
	I2C1Handle.Instance = I2C1;

	I2C1Handle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
	I2C1Handle.Init.ClockSpeed      = 400000;
	I2C1Handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2C1Handle.Init.DutyCycle       = I2C_DUTYCYCLE_2;
	I2C1Handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	I2C1Handle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

	if(HAL_I2C_Init(&I2C1Handle) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}
}
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	/*##-1- Enable peripherals and GPIO Clocks #################################*/
	/* Enable GPIO TX/RX clock */
	__HAL_RCC_GPIOB_CLK_ENABLE();
	/* Enable I2C1 clock */
	__HAL_RCC_I2C1_CLK_ENABLE();

	/*##-2- Configure peripheral GPIO ##########################################*/
	/* I2C TX GPIO pin configuration  */
	GPIO_InitStruct.Pin       = GPIO_PIN_8;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;

	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* I2C RX GPIO pin configuration  */
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;

	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void Error_Handler()
{
	char *msg = "Something went wrong!\r\n";
	HAL_UART_Transmit(&huart2, (uint8_t*) msg, strlen(msg), 0xFFFF);
}
