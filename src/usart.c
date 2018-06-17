/*
 * usart.c
 *      Author: andre
 */
#include "usart.h"
void MX_USART2_UART_Init(void)
{
	huart2.Instance 				= USART2;
	huart2.Init.BaudRate 			= 9600;
	huart2.Init.WordLength 			= UART_WORDLENGTH_8B;
	huart2.Init.StopBits 			= UART_STOPBITS_1;
	huart2.Init.Parity 				= UART_PARITY_NONE;
	huart2.Init.Mode 				= UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl 			= UART_HWCONTROL_NONE;
	HAL_UART_Init(&huart2);
}
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	if(huart->Instance==USART2)
	{
		__GPIOA_CLK_ENABLE();
		__USART2_CLK_ENABLE();

		/*USART2 GPIO Configuration
	    PA2     ------> USART2_TX
	    PA3     ------> USART2_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		HAL_NVIC_SetPriority(USART2_IRQn,0,1);
		HAL_NVIC_EnableIRQ(USART2_IRQn);
	}
}
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART2)
	{
		__HAL_RCC_USART2_FORCE_RESET();
		__HAL_RCC_USART2_RELEASE_RESET();
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2);
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_3);

		HAL_NVIC_DisableIRQ(USART2_IRQn);
	}
};

