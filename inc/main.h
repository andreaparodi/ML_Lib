/*
 * main.h
 *      Author: andre
 */
#ifndef MAIN_H_
#define MAIN_H_

//#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "vector_extraction.h"
#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "i2c.h"
#include "lsm6dsl.h"
#include "usart.h"
#include "gpio.h"
#include "node.h"
#include "pc.h"
#include "knn.h"

//valore di inizializzazione per i pesi
#define defaultWeight 1
//valore di inizializzazione per i pesi
#define defaultBias 0
//valore di inizializzazione per i valori
#define defaultNodeValue 0
//numero di esempi nel training set
#define nOfSamples 190
//numero di cicli di training sullo stesso esempio
#define max_rep 1
//numero dei vettori di training da non considerare per ogni classe
#define sampleToAvoid 60
//tempo tra due letture
#define sampleTime 100
//elementi di un vettore di training/da classificare
#define vectorLength 50
//numero di volte che vengono scelte delle coppie se in modalità training random
#define randomTrainingModeCycles 500

#define testSetSize 100


#define NOT_SHOW_SENS_DATA 	0
#define SHOW_SENS_DATA 		1



UART_HandleTypeDef huart2;
UART_HandleTypeDef UARTHandle1;

int main(void);
int Rand_value_acc(void);

#endif /* MAIN_H_ */




