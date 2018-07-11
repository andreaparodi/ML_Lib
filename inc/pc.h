
#ifndef PC_H_
#define PC_H_

#include "main.h"

#define nOfFeatures 	15
#define nOfSamples 		100
#define nOfFeatures 	15
#define alpha_learning 	0.1
#define cycles 			100

void train_hyperplane(float tr_set[nOfSamples][nOfFeatures],int training_labels[], float w[], float bias);
int predictLabel(float w[], float in_vect[], float b);

#endif /* PC_H_ */
