
#ifndef KNN_H_
#define KNN_H_

#include "main.h"
#define k 11


float calculateDistance(float feature_vect1[], float feature_vect2[]);
void findKNN(float trainingFeatures[nOfSamples][nOfFeatures], int index[], float sampleFeatures[]);
int classificate(int labels[], int indexes[]);

#endif /* KNN_H_ */
