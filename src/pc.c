#include "pc.h"

void train_hyperplane(float tr_set[nOfSamples][nOfFeatures],
		int training_labels[], float w[], float bias)
{
	int labels[nOfSamples] = { 0 };
		float tempVect[nOfFeatures] = { 0 };
		//conversione etichette
		for (int i = 0; i < nOfSamples; i++)
		{
			if (training_labels[i] == 0)
			{
				labels[i] = -1;
			}
			else
			{
				labels[i] = 1;
			}
		}
		int temp_label = 0;

		for (int rep = 0; rep < cycles; rep++)
		{
			for (int i = 0; i < nOfSamples; i++)
			{
				for (int p = 0; p < nOfFeatures; p++)
				{
					tempVect[p] = tr_set[i][p];
				}
				temp_label = predictLabel(w, tempVect, bias);
				if (labels[i] != temp_label)
				{
					int adj = labels[i] - temp_label;
					for (int j = 0; j < nOfFeatures; j++)
					{
						w[j] = w[j] + (alpha_learning*adj*tr_set[i][j]);
					}
					bias = bias + (alpha_learning*adj);
				}
			}
		}
		//serve per verifica
		int pos_counter = 0;
		for (int i = 0; i < nOfSamples; i++)
		{
			int label = predictLabel(w, tr_set[i], bias);
			//printf("%i\n", label);
			if (label == 1)
			{
				pos_counter++;
			}
		}
		//printf("%i\n", pos_counter);
}

int predictLabel(float w[], float in_vect[], float b)
{
	float res = 0;
	for (int i = 0; i < nOfFeatures; i++)
	{
		res = res + (w[i] * in_vect[i]);
	}
	res = res + b;
	if (res >= 0)
	{
		res = 1;
	}
	else
	{
		res = -1;
	}
	return res;
}

