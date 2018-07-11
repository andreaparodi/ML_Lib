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
#define nOfSamples 100
//numero di cicli di training sullo stesso esempio
#define max_rep 1
//numero dei vettori di training da non considerare per ogni classe
#define sampleToAvoid 15
//tempo tra due letture
#define sampleTime 100
//elementi di un vettore di training/da classificare
#define vectorLength 50
//numero di volte che vengono scelte delle coppie se in modalità training random
#define randomTrainingModeCycles 500

#define testSetSize 50
/*
 * Random setup = tutti gli elementi della rete sono inizializzati random
 * Load from function = carica i pesi e i bias della rete che sono cablati dentro una funzione, generabile
 * attraverso la funzione printNetwork
 * Load from file = carica i pesi e i bias della rete da file di testo (non funzionante al momento)
 * Train from data in progra = utilizza un dataset cablato nel programma per effettuare il training della rete
 * */
#define WORK_MODE_RANDOM_SETUP 						0
#define WORK_MODE_LOAD_NETWORK_FROM_FUNCTION 		1
#define WORK_MODE_LOAD_NETWORK_FROM_FILE	 		2
#define WORK_MODE_TRAIN_FROM_DATA_IN_PROGRAM		3
/*
 * Abilita o disabilita il crosstrain della rete (utilizzare una parte di training set come test set)
 * */

/*
 * Training mode random = vengono scelte delle coppie di vettori, uno per ogni classe,e si effettua il training
 * su di esse, si ripete questa procedura n (500) volte (non garantisce quindi che tutti gli elementi del
 * training vengano utilizzati nell'addestramento della rete, un buon numero di elementi verrà utilizzato
 * più volte)
 * Training mode full = il training viene fatto utilizzando una volta ogni elemento del training set, alternando
 * per classe
 * */
#define TRAINING_MODE_RANDOM	0
#define TRAINING_MODE_FULL		1

#define NOT_SHOW_SENS_DATA 	0
#define SHOW_SENS_DATA 		1



UART_HandleTypeDef huart2;
UART_HandleTypeDef UARTHandle1;

int main(void);
int Rand_value_acc(void);

#endif /* MAIN_H_ */




