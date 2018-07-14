
#ifndef KNN_H_
#define KNN_H_

#include "main.h"

#define k 13

#define EUCLIDEAN_DISTANCE 0
#define MANHATTAN_DISTANCE 1

#define VOTE_MAJORITY	0
#define VOTE_WEIGHTED	1

float calculateDistance(float feature_vect1[], float feature_vect2[], int type);
void findKNN(float trainingFeatures[nOfSamples][nOfFeatures], int index[], float sampleFeatures[],int dis_type);
int classificate(int labels[], int indexes[], int vote_type, float tr_set[nOfSamples][nOfFeatures], float vect[], int dist_type);
float weightedVote(float dist);

#endif /* KNN_H_ */
