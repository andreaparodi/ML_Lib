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
void findKNN(float trainingFeatures[nOfSamples][nOfFeatures],
		int index[], float sampleFeatures[], int dis_type)
{
	float distances[nOfSamples] = { 0 };
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

int classificate(int labels[], int indexes[], int vote_type,
		float tr_set[nOfSamples][nOfFeatures], float vect[], int dist_type)
{
	int score = 0;
	int threshold = 0;
	if(vote_type==VOTE_MAJORITY)
	{
		for (int i = 0; i < k; i++)
		{
			int tmp = indexes[i];
			score = score + labels[tmp];
		}
		threshold = floor(k/2);
		if (score > threshold)
			score = 1;
		else
			score = 0;
	}
	else if(vote_type==VOTE_WEIGHTED)
	{
		float dist=0;
		float weight=0;
		float result=0;
		for (int i = 0; i < k; i++)
		{
			int tmp = indexes[i];
			dist=calculateDistance(tr_set[i],vect,dist_type);
			weight=weightedVote(dist);

			if(labels[tmp]==1)
			{
				result=result+weight;
			}
			else
			{
				result=result-weight;
			}
		}
		if(result>0)
			score=1;
		else
			score=0;
	}
	return score;
}
float weightedVote(float dist)
{
	float result=0;
	result=1/(1+dist);
	return result;
}


