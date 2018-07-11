/*
 * lsm6dsl.c
 *      Author: andre
 */
#include "lsm6dsl.h"

uint8_t LSM6DSL_Who_Am_I(void)
{
	const uint8_t I2C_RXBUFFERSIZE = 1;
	uint8_t I2C_RxBuffer[I2C_RXBUFFERSIZE];

	I2C_RxBuffer[0] = LSM6DSL_WHO_AM_I;

	HAL_I2C_Master_Transmit(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR<<1  & 0xFE, (uint8_t *)&I2C_RxBuffer[0], 1, 10000);
	HAL_I2C_Master_Receive(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR<<1 | 1, (uint8_t *)&I2C_RxBuffer[0], 1, 10000);

	return I2C_RxBuffer[0];
}
//funzione di lettura dati accelerometro
void LSM6DSL_ReadAcceleration(float vect[])
{
	const uint8_t	I2C_RXBUFFERSIZE = 2;

	uint8_t I2C_RxBufferX[I2C_RXBUFFERSIZE];
	uint8_t I2C_RxBufferY[I2C_RXBUFFERSIZE];
	uint8_t I2C_RxBufferZ[I2C_RXBUFFERSIZE];

	float X_acc, Y_acc, Z_acc;
	float acc_sens_table = 0.061;

	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR<<1 | 1,
			LSM6DSL_OUTX_L_XL, 1, (uint8_t *)&I2C_RxBufferX[0], 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR<<1 | 1,
			LSM6DSL_OUTX_H_XL, 1, (uint8_t *)&I2C_RxBufferX[1], 1, 10000);
	int16_t dataX = (((uint16_t)I2C_RxBufferX[1]<<8 | I2C_RxBufferX[0]));
	X_acc = (float)dataX;

	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR<<1 | 1,
			LSM6DSL_OUTY_L_XL, 1, (uint8_t *)&I2C_RxBufferY[0], 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR<<1 | 1,
			LSM6DSL_OUTY_H_XL, 1, (uint8_t *)&I2C_RxBufferY[1], 1, 10000);
	int16_t dataY = (((uint16_t)I2C_RxBufferY[1]<<8 | I2C_RxBufferY[0]));
	Y_acc = (float)dataY;

	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR<<1 | 1,
			LSM6DSL_OUTZ_L_XL, 1, (uint8_t *)&I2C_RxBufferZ[0], 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR<<1 | 1,
			LSM6DSL_OUTZ_H_XL, 1, (uint8_t *)&I2C_RxBufferZ[1], 1, 10000);
	int16_t dataZ = (((uint16_t)I2C_RxBufferZ[1]<<8 | I2C_RxBufferZ[0]));
	Z_acc = (float)dataZ;

	vect[0]=X_acc*acc_sens_table/1000;
	vect[1]=Y_acc*acc_sens_table/1000;
	vect[2]=Z_acc*acc_sens_table/1000;
}

//Funzione di lettura dei dati rilevati dal giroscopio
void LSM6DSL_ReadGyro(float vect[])
{
	const uint8_t	I2C_RXBUFFERSIZE = 2;

	uint8_t I2C_RxBufferX[I2C_RXBUFFERSIZE];
	uint8_t I2C_RxBufferY[I2C_RXBUFFERSIZE];
	uint8_t I2C_RxBufferZ[I2C_RXBUFFERSIZE];

	float X_gyr, Y_gyr, Z_gyr;
	float gyro_sensitivity =8.75;
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR<<1 | 1,
			LSM6DSL_OUTX_L_G, 1, (uint8_t *)&I2C_RxBufferX[0], 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR<<1 | 1,
			LSM6DSL_OUTX_H_G, 1, (uint8_t *)&I2C_RxBufferX[1], 1, 10000);
	int16_t dataX = (((uint16_t)I2C_RxBufferX[1]<<8 | I2C_RxBufferX[0]));
	X_gyr = (float)dataX;

	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR<<1 | 1,
			LSM6DSL_OUTY_L_G, 1, (uint8_t *)&I2C_RxBufferY[0], 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR<<1 | 1,
			LSM6DSL_OUTY_H_G, 1, (uint8_t *)&I2C_RxBufferY[1], 1, 10000);
	int16_t dataY = (((uint16_t)I2C_RxBufferY[1]<<8 | I2C_RxBufferY[0]));
	Y_gyr = (float)dataY;

	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR<<1 | 1,
			LSM6DSL_OUTZ_L_G, 1, (uint8_t *)&I2C_RxBufferZ[0], 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR<<1 | 1,
			LSM6DSL_OUTZ_H_G, 1, (uint8_t *)&I2C_RxBufferZ[1], 1, 10000);
	int16_t dataZ = (((uint16_t)I2C_RxBufferZ[1]<<8 | I2C_RxBufferZ[0]));
	Z_gyr = (float)dataZ;

	vect[0]=X_gyr*gyro_sensitivity/1000;
	vect[1]=Y_gyr*gyro_sensitivity/1000;
	vect[2]=Z_gyr*gyro_sensitivity/1000;
}


void LSM6DSL_Config()
{
	const uint8_t I2C_TXBUFFERSIZE = 10;	//Dimensione pari al numero totale di registri inizializzati

	uint8_t I2C_TxBuffer[I2C_TXBUFFERSIZE];

	/********************************************************
	* Inizializzazione di  LSM6DSL_CTRL1_XL: "0011 00 ? 1" (0x31 oppure 0x33)
	* ODR: 52Hz (low power), FullScale = +-2g,
	********************************************************/
	I2C_TxBuffer[0] = 0x33;

	/*********************************************************
	* Inizializzazione di LSM6DSL_CTRL2_G "0011 00 00"
	* ODR 52 Hz (low power)
	* FullScale 250 dps
	********************************************************/
	I2C_TxBuffer[1] = 0x30;

	/*********************************************************
	* Inizializzazione di LSM6DSL_CTRL3_C: "00000100"
	* Configurazione di default
	*********************************************************/
	I2C_TxBuffer[2] = 0x04;

	/**********************************************************
	* Inizializzazione di LSM6DSL_CTRL4_C: "00000000"
	* No "Den" mode per l'accelerometro
	* No "Sleep" mode per il giroscopio
	* Segnali di interrupt separati
	* I2C e SPI abilitate
	* No LPF1 per il giroscopio
	**********************************************************/
	I2C_TxBuffer[3] = 0x00;

	/***********************************************************
	* Inizializzazione di LSM6DSL_CTRL5_C: "00000000"
	* Configurazione di default
	* No rounding
	* No self-test
	***********************************************************/
	I2C_TxBuffer[4] = 0x00;

	/***********************************************************
	* Inizializzazione di LSM6DSL_CTRL6_C: "00000000"
	* Configurazione di default
	* High performance per l'accelerometro
	* Peso offset: 2^-10 g/LSB
	***********************************************************/
	I2C_TxBuffer[5] = 0x00;

	/**********************************************************
	* Inizializzazione di LSM6DSL_CTRL7_G: "00000000"
	* Configurazione di default
	* High performance per il giroscopio
	* No HPF
	* No rounding
	**********************************************************/
	I2C_TxBuffer[6] = 0x00;

	/*********************************************************
	* Inizializzazione alla configurazione di default
	* di LSM6DSL_CTRL8_XL: "00001000"
	*********************************************************/
	I2C_TxBuffer[7] = 0x08;

	/***********************************************************
	* Inizializzazione di LSM6DSL_CTRL9_XL: "00000000"
	* Configurazione di default
	* Non considerati argomenti Den (è disabilitato)
	* No soft-iron correction
	***********************************************************/
	I2C_TxBuffer[8] = 0x00;

	/**********************************************************
	* Inizializzazione di LSM6DSL_CTRL10_C: "00000000"
	* Configurazione di default
	* No wrist algorithm
	* No timestamp
	* No pedo count
	* No tilt
	* Extra function disabled
	**********************************************************/
	I2C_TxBuffer[9] = 0x00;

	HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR << 1 & 0xFE,
			LSM6DSL_CTRL1_XL, 1, (uint8_t *)&I2C_TxBuffer[0], 1, 10000);
	HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR << 1 & 0xFE,
			LSM6DSL_CTRL2_G, 1, (uint8_t *)&I2C_TxBuffer[1], 1, 10000);
	HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR << 1 & 0xFE,
			LSM6DSL_CTRL3_C, 1, (uint8_t *)&I2C_TxBuffer[2], 1, 10000);
	HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR << 1 & 0xFE,
			LSM6DSL_CTRL4_C, 1, (uint8_t *)&I2C_TxBuffer[3], 1, 10000);
	HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR << 1 & 0xFE,
			LSM6DSL_CTRL5_C, 1, (uint8_t *)&I2C_TxBuffer[4], 1, 10000);
	HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR << 1 & 0xFE,
			LSM6DSL_CTRL6_C, 1, (uint8_t *)&I2C_TxBuffer[5], 1, 10000);
	HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR << 1 & 0xFE,
			LSM6DSL_CTRL7_C, 1, (uint8_t *)&I2C_TxBuffer[6], 1, 10000);
	HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR << 1 & 0xFE,
			LSM6DSL_CTRL8_XL, 1, (uint8_t *)&I2C_TxBuffer[7], 1, 10000);
	HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR << 1 & 0xFE,
			LSM6DSL_CTRL9_XL, 1, (uint8_t *)&I2C_TxBuffer[8], 1, 10000);
	HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR << 1 & 0xFE,
			LSM6DSL_CTRL10_C, 1, (uint8_t *)&I2C_TxBuffer[9], 1, 10000);
	//HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DSL_SLAVE_ADDR << 1 & 0xFE, LSM6DS0_ORIENT_CFG_G, 1, (uint8_t *)&I2C_TxBuffer[10], 1, 10000);
}

