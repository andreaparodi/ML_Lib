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

	for (i = 0; i<vectorLength; i++)
	{
		var = var + pow((vect[i] - mean), 2);
	}
	var = var / vectorLength;
	return var;
}

float calculateCorr(float vect1[], float vect2[], float med1, float med2)
{
	float corr = 0.0;
	float temp = 0.0;
	float nom = 0;
	float den1 = 0;
	float den2 = 0;
	for (int i = 0; i<vectorLength; i++)
	{
		temp = (vect1[i] - med1);
		temp = temp * (vect2[i] - med2);
		nom = nom + temp;
		temp = (vect1[i] - med1);
		temp = temp*temp;
		den1 = den1 + temp;

		temp = (vect2[i] - med2);
		temp = temp*temp;
		den2 = den2 + temp;
	}
	den1=sqrtf(den1);
	den2=sqrtf(den2);
	corr = nom / (den1*den2);
	return corr;
}

