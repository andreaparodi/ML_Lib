/*
 * node.h
 *
 *  Created on: 08 giu 2018
 *      Author: andre
 */

#ifndef NODE_H_
#define NODE_H_

#include "main.h"
#include  <stdio.h>

//numero delle features estratte = numero degli input
#define nOfFeatures 15
//numero dei nodi "hidden"
#define nOfHiddenNodes 30
//numero delle classi = numero dei nodi di out
#define nOfOutputNodes 1
//parametro di apprendimento //"eta" da esempio
#define learningRate 0.175
//secondo parametro di apprendimento //"alpha" da esempio
#define alpha 0
//numero totale dei pesi della rete
#define nOfWeights ((nOfOutputNodes*nOfHiddenNodes)+(nOfHiddenNodes*nOfFeatures))
//numero totale dei bias della rete
#define nOfBiases (nOfOutputNodes+nOfHiddenNodes)
//errore massimo accettato in fase di training
#define thresholdError 0.1

typedef struct
{
	float value;
	float weights[nOfHiddenNodes];
}
InputNode;

typedef struct
{
	float value;
	float weights[nOfOutputNodes];
	float bias;
}
HiddenNode;

typedef struct
{
	float value;
	float bias;
}
OutputNode;

void feedForward(InputNode in[], HiddenNode hn[], OutputNode on[]);
//setup con pesi random nell'intervallo [-0.5; 0.5]
void randomSetupNodes(InputNode in[], HiddenNode hn[], OutputNode on[]);
void loadTrainedNetwork(InputNode in[], HiddenNode hn[], OutputNode on[]);
void loadTrainedNetworkFromFile(InputNode in[], HiddenNode hn[], OutputNode on[]);

void train(InputNode in[], HiddenNode hn[], OutputNode on[], float inputFeatures[], int label);
int calculateOutput(InputNode in[], HiddenNode hn[], OutputNode on[], float inputFeatures[]);

double sigmoid(double x);
float fsigmoid(float x);
float generateRandomWeights();
void printNetwork(InputNode in[], HiddenNode hn[], OutputNode on[], float weights[], float biases[]);

#endif /* NODE_H_ */
