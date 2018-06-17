/*
 * usart.h
 *      Author: andre
 */

#ifndef USART_H_
#define USART_H_

#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"

void USART1_Init();
void MX_USART2_UART_Init(void);
void HAL_UART_MspInit();
void HAL_UART_MspDeInit();
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif /* USART_H_ */
