#include "knn.h"
//calcola la distanza tra due vettori calcolando la distanza euclidea tra le features
float calculateDistance(float feature_vect1[], float feature_vect2[])
{
	float distance = 0.0;
	float temp = 0.0;
	for (int i = 0; i < nOfFeatures; i++)
	{
		temp = (feature_vect1[i] - feature_vect2[i]);
		distance = distance + pow(temp, 2);
	}
	temp = 0.0;
	distance = sqrt(distance);
	return distance;
}

//calcola tutte le possibili distanze e le ordina
void findKNN(float trainingFeatures[nOfSamples][nOfFeatures], int index[], float sampleFeatures[])
{
	//copio matrice features per non modificarla nel main
	float distances[nOfSamples] = { 0 };

	//calcolo delle distanze
	for (int i = 0; i < nOfSamples; i++)
	{
		distances[i] = calculateDistance(trainingFeatures[i], sampleFeatures);
	}
	for (int i = 0; i <nOfSamples; i++)                     //Loop for ascending ordering
	{
		for (int j = 0; j < nOfSamples; j++)             //Loop for comparing other values
		{
			if (distances[j] > distances[i])                //Comparing other array elements
			{
				float tmp = distances[i];         //Using temporary variable for storing last value
				distances[i] = distances[j];            //replacing value
				distances[j] = tmp;             //storing last value

				int tmpIndex = index[i];
				index[i] = index[j];
				index[j] = tmpIndex;
			}
		}
	}
}

int classificate(int labels[], int indexes[])
{
	int score = 0;
	float temp=  0.0;
	int threshold = 0;
	for (int i = 0; i < k; i++)
	{
		//labels contiene 1 oppure 0 a seconda che sia una classe o l'altra
		int tmp = indexes[i];
		score = score + labels[tmp];
	}
	temp = k/2;
	threshold = floor(k/2);
	if (score > threshold)
		return 1;
	else
		return 0;
}



