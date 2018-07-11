/*
 * vector_extraction.h
 *      Author: andre
 */

#ifndef VECTOR_EXTRACTION_H_
#define VECTOR_EXTRACTION_H_

#include "math.h"
#include "main.h"

#define cutoff_correlation 0.1

float calculateMean(float vect[]);
float calculateVar(float vect[], float mean);
float calculateCorr(float vect1[], float vect2[], float med1, float med2);

#endif /* VECTOR_EXTRACTION_H_ */
