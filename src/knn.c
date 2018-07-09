#include "knn.h"
//calcola la distanza tra due vettori calcolando la distanza euclidea tra le features
float calculateDistance(float feature_vect1[], float feature_vect2[], int type)
{
	float distance = 0.0;
	float temp = 0.0;
	if (type==EUCLIDEAN_DISTANCE)
	{
	for (int i = 0; i < nOfFeatures; i++)
	{
		temp = (feature_vect1[i] - feature_vect2[i]);
		distance = distance + pow(temp, 2);
	}
	temp = 0.0;
	distance = sqrt(distance);
	}
	else if(type==MANHATTAN_DISTANCE)
	{
		for (int i = 0; i < nOfFeatures; i++)
			{
				distance = distance +fabs(feature_vect1[i] - feature_vect2[i]);
			}
	}
	return distance;
}

//calcola tutte le possibili distanze e le ordina
void findKNN(float trainingFeatures[nOfSamples][nOfFeatures], int index[], float sampleFeatures[])
{
	float distances[nOfSamples] = { 0 };
	int dis_type=EUCLIDEAN_DISTANCE;
	//calcolo delle distanze
	for (int i = 0; i < nOfSamples; i++)
	{
		distances[i] = calculateDistance(trainingFeatures[i], sampleFeatures, dis_type);
	}
	for (int i = 0; i <nOfSamples; i++)
	{
		for (int j = 0; j < nOfSamples; j++)
		{
			if (distances[j] > distances[i])
			{
				float tmp = distances[i];
				distances[i] = distances[j];
				distances[j] = tmp;

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
	int threshold = 0;
	for (int i = 0; i < k; i++)
	{
		int tmp = indexes[i];
		score = score + labels[tmp];
	}
	threshold = floor(k/2);
	if (score > threshold)
		return 1;
	else
		return 0;
}



