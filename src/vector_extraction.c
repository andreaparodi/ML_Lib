/*
 * vector_extraction.c
 *      Author: andre
 */
#include "vector_extraction.h"


float calculateMean(float vect[])
{
	float mean = 0.0;

	int i;
	for (i = 0; i<vectorLength; i++)
	{
		mean = mean + vect[i];
	}
	mean = mean / vectorLength;
	return mean;
}
float calculateVar(float vect[], float mean)
{
	float var = 0.0;
	int i;

//debug
	/*
	char buffer[100];
	char *newline = "\n\r";
char *men=" - ";
*/
	for (i = 0; i<vectorLength; i++)
	{
		/*
		snprintf(buffer, sizeof buffer, "%f", vect[i]);
		HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer), 0xFFFF);
		//HAL_UART_Transmit(&huart2, (uint8_t*) newline, strlen(newline), 0xFFFF);

		HAL_UART_Transmit(&huart2, (uint8_t*) men, strlen(men), 0xFFFF);

		snprintf(buffer, sizeof buffer, "%f", mean);
		HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer), 0xFFFF);
		HAL_UART_Transmit(&huart2, (uint8_t*) newline, strlen(newline), 0xFFFF);
*/
		var = var + pow((vect[i] - mean), 2);
		//sempre parte della verifica sul calcolo della varianza
/*
		snprintf(buffer, sizeof buffer, "%f", var);
		HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer), 0xFFFF);
		HAL_UART_Transmit(&huart2, (uint8_t*) newline, strlen(newline), 0xFFFF);
		HAL_Delay(400);
		*/
	}
	var = var / vectorLength;
	return var;
}

float calculateCorr(float vect1[], float vect2[], float med1, float med2, float stdDev1, float stdDev2)
{
	float corr = 0.0;
	float temp = 0.0;
	int i;
	for (i = 0; i<vectorLength; i++)
	{
		temp = (vect1[i] - med1);
		temp = temp * (vect2[i] - med2);
		corr = corr + temp;
		temp = 0.0;
	}
	corr = corr / vectorLength;

	//serve un controllo su deviazioni standard diverse da zero
	int tempStdDev1=fabs(stdDev1);
	int tempStdDev2=fabs(stdDev2);
	if(tempStdDev1<1 || tempStdDev2<1)
	{
		if(stdDev1>0)
		{
			stdDev1=cutoff_correlation;
		}
		else
		{
			stdDev1=-cutoff_correlation;
		}
		if(stdDev2>0)
		{
			stdDev2=cutoff_correlation;
		}
		else
		{
			stdDev2=-cutoff_correlation;
		}
	}
	corr = corr / (stdDev1*stdDev2);
	if(corr>1)
		corr=1;
	else if(corr<-1)
		corr=-1;
	return corr;
}

