/*
 * lsm6dsl.h
 *      Author: andre
 */

#ifndef LSM6DSL_H_
#define LSM6DSL_H_

#pragma once
#include "main.h"

#define LSM6DSL_WHO_AM_I_VAL		0x6A //(0110 1010) valore di default del registro who am i
#define LSM6DSL_WHO_AM_I 		    0x0F //indirizzo del registro who am i

#define LSM6DSL_SLAVE_ADDR			0x6B //0x6A slave address della i2c del sensore

#define LSM6DSL_CTRL1_XL			0x10
#define LSM6DSL_CTRL2_G				0x11
#define LSM6DSL_CTRL3_C				0x12
#define LSM6DSL_CTRL4_C				0x13
#define LSM6DSL_CTRL5_C				0x14
#define LSM6DSL_CTRL6_C				0x15
#define LSM6DSL_CTRL7_C				0x16
#define LSM6DSL_CTRL8_XL			0x17
#define LSM6DSL_CTRL9_XL			0x18
#define LSM6DSL_CTRL10_C			0x19

#define LSM6DSL_OUTX_L_G			0x22 //registri dove leggere i dati del giroscopio
#define LSM6DSL_OUTX_H_G			0x23
#define LSM6DSL_OUTY_L_G			0x24
#define LSM6DSL_OUTY_H_G			0x25
#define LSM6DSL_OUTZ_L_G			0x26
#define LSM6DSL_OUTZ_H_G			0x27

#define LSM6DSL_OUTX_L_XL			0x28//registri dove leggere i dati dell'accelerometro
#define LSM6DSL_OUTX_H_XL			0x29
#define LSM6DSL_OUTY_L_XL			0x2A
#define LSM6DSL_OUTY_H_XL			0x2B
#define LSM6DSL_OUTZ_L_XL			0x2C
#define LSM6DSL_OUTZ_H_XL			0x2D


FunctionalState LSM6DSL_present;

uint8_t LSM6DSL_Who_Am_I(void);
void LSM6DSL_Config();

void LSM6DSL_ReadAcceleration(float vect[]);	//Definizione della funzione di lettura dei dati dell'accelerometro.
void LSM6DSL_ReadGyro(float vect[]);			//Definizione della funzione di lettura dei dati del giroscopio.

#endif /* LSM6DSL_H_ */
