/*
 * node.c
 *      Author: andre
 */
#include "node.h"

double sigmoid(double x)
{
	return tanh(x);
}
//attualmente in uso
float fsigmoid(float x)
{
	float result = 1 / (1 + expf(-x));
	return result;
}
float ftanh(float x)
{
	return (float)tanh(x);
}

void feedForward(InputNode in[], HiddenNode hn[], OutputNode on[])
{
	float hValues[nOfHiddenNodes] = {0};
	float oValues[nOfOutputNodes] = { 0 };

	for (int h = 0; h < nOfHiddenNodes; h++)
	{
		//bias dello specifico nodo hidden
		hValues[h] = hn[h].bias;
		for (int i = 0; i < nOfFeatures; i++)
		{
			//calcolo dell'argomento della funzione di attivazione come somma dei prodotti in*peso
			hValues[h] = hValues[h] + (in[i].value*in[i].weights[h]);

			//applicazione della funzione di attivazione
			hn[h].value = fsigmoid(hValues[h]);
		}
	}
	for (int o = 0; o < nOfOutputNodes; o++)
	{
		//bias dello specifico nodo di output
		oValues[o] = on[o].bias;
		for (int h = 0; h < nOfHiddenNodes; h++)
		{
			//calcolo dell'argomento della funzione di attivazione come somma dei prodotti hid*peso
			oValues[o] = oValues[o] + (hn[h].value*hn[h].weights[o]);
			//applicazione della funzione di attivazione
			on[o].value = fsigmoid(oValues[o]);
		}
	}
}
float calculateOutput(InputNode in[], HiddenNode hn[], OutputNode on[], float inputFeatures[])
{
	for (int i = 0; i < nOfFeatures; i++)
	{
		in[i].value = inputFeatures[i];
	}
	feedForward(in, hn, on);
	float result = on[0].value;
	return result;
}
int calculateSampleLabel(InputNode in[], HiddenNode hn[], OutputNode on[], float inputFeatures[])
{
	float val = calculateOutput(in,hn,on,inputFeatures);
	if(val>0.5)
		return 1;
	else
		return 0;
}
void randomSetupNodes(InputNode in[], HiddenNode hn[], OutputNode on[])
{
	for (int i = 0; i < nOfFeatures; i++)
	{
		in[i].value = defaultNodeValue;
		for (int h = 0; h < nOfHiddenNodes; h++)
		{
			in[i].weights[h] = generateRandomWeights();
		}
	}
	for (int h = 0; h < nOfHiddenNodes; h++)
	{
		hn[h].value = defaultNodeValue;
		hn[h].bias = defaultBias;
		for (int o = 0; o < nOfOutputNodes; o++)
		{
			hn[h].weights[o] = generateRandomWeights();
		}
	}
	for (int o = 0; o < nOfOutputNodes; o++)
	{
		on[o].value = defaultNodeValue;
		on[o].bias = defaultBias;
	}
}

/*
void loadTrainedNetworkFromFile(InputNode in[], HiddenNode hn[], OutputNode on[])
{
	//FILE* network = NULL;
	float temp = 0.0;

	FILE* network = fopen("network.txt", "a"); //"a" serve per crearlo


	network = fopen("network.txt", "r");
	if (network != NULL)
	{

		//scrittura pesi e bias sui nodi
		for (int i = 0; i < nOfFeatures; i++)
		{
			for (int h = 0; h < nOfHiddenNodes; h++)
			{
				//fscanf_s(network, "%f", &temp);
				fscanf(network, "%f", &temp);
				in[i].weights[h] = temp;
			}
		}
		for (int h = 0; h < nOfHiddenNodes; h++)
		{
			for (int o = 0; o < nOfOutputNodes; o++)
			{
				//fscanf_s(network, "%f", &temp);
				fscanf(network, "%f", &temp);
				hn[h].weights[o] = temp;
			}
		}
		for (int h = 0; h < nOfHiddenNodes; h++)
		{
			//fscanf_s(network, "%f", &temp);
			fscanf(network, "%f", &temp);
			hn[h].bias = temp;
		}
		for (int o = 0; o < nOfOutputNodes; o++)
		{
			//fscanf_s(network, "%f", &temp);
			fscanf(network, "%f", &temp);
			on[o].bias = temp;
		}
	}
	else
	{
		char *mess ="File not found\n\r";
		HAL_UART_Transmit(&huart2, (uint8_t*)mess, strlen(mess), 0xFFFF);
		//printf("File not found!");
		//HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
	}
	fclose(network);
}
*/


void train(InputNode in[], HiddenNode hn[], OutputNode on[], float inputFeatures[nOfSamples][nOfFeatures], int labels[])
{
	//float delta_h[nOfHiddenNodes] = {0};
	//float delta_o[nOfOutputNodes] = {0};

	float error=0;
	for(int ind=0;ind<nOfSamples/2;ind++)
	{
		rec_train(in,hn,on,inputFeatures[ind],labels[ind]);
/*
		calculateSampleLabel(in, hn, on, inputFeatures[ind]);
		error=(fabs)(labels[ind]-on[0].value);
		//se l'errore è maggiore di un valore scelto viene effettuato ancora il training finchè la condizione non è soddisfatta
		if(error>thresholdError)
		{
			rec_train(in,hn,on,inputFeatures[ind],labels[ind]);
		}
		*/
		rec_train(in,hn,on,inputFeatures[ind+nOfSamples/2],labels[ind+nOfSamples/2]);
/*
				calculateSampleLabel(in, hn, on, inputFeatures[ind+nOfSamples/2]);
				error=(fabs)(labels[ind+nOfSamples/2]-on[0].value);
				//se l'errore è maggiore di un valore scelto viene effettuato ancora il training finchè la condizione non è soddisfatta
				if(error>thresholdError)
				{
					rec_train(in,hn,on,inputFeatures[ind+nOfSamples/2],labels[ind+nOfSamples/2]);
				}
				*/
	}
}
void rec_train(InputNode in[], HiddenNode hn[], OutputNode on[], float inputFeatures[], int label)
{
	float delta_h[nOfHiddenNodes] = {0};
		float delta_o[nOfOutputNodes] = {0};

		float error=0;
			calculateSampleLabel(in, hn, on, inputFeatures);

			//calcolo dei delta per il livello di output
			for (int o = 0; o < nOfOutputNodes; o++)
			{
				delta_o[o] = (label - on[o].value)*on[o].value*(1.0 - on[o].value);
			}
			//calcolo dei delta per il livello hidden
			for (int h = 0; h < nOfHiddenNodes; h++)
			{
				for (int o = 0; o < nOfOutputNodes; o++)
				{
					delta_h[h] = delta_h[h] + (delta_o[o]*hn[h].weights[o]);
				}
				delta_h[h] = delta_h[h] * ((hn[h].value)*(1- hn[h].value));
			}
			//aggiornamento pesi input-hidden layer
			for (int h = 0; h < nOfHiddenNodes; h++)
			{
				hn[h].bias = hn[h].bias + learningRate*delta_h[h];
				//soluzione temporanea per tenere la modifica dei pesi, sarebbe da cambiare con una matrice per verificare gli aggiustamenti
				float temp = 0;
				for (int i = 0; i < nOfFeatures; i++)
				{
					temp = learningRate*in[i].value*delta_h[h];
					in[i].weights[h] = in[i].weights[h] + temp;
					temp = 0;
				}
			}
			for (int o = 0; o < nOfOutputNodes; o++)
			{
				on[o].bias = learningRate*delta_o[o];
				//soluzione temporanea per tenere la modifica dei pesi, sarebbe da cambiare con una matrice (vettore se nOutput=1) per verificare gli aggiustamenti
				float temp = 0;
				for (int h = 0; h < nOfHiddenNodes; h++)
				{
					temp = learningRate*hn[h].value*delta_o[o];
					hn[h].weights[o] = hn[h].weights[o] + temp;
					temp = 0;
				}
			}
			calculateSampleLabel(in, hn, on, inputFeatures);
			error=(fabs)(label-on[0].value);
			//se l'errore è maggiore di un valore scelto viene effettuato ancora il training finchè la condizione non è soddisfatta
			if(error>thresholdError)
			{
				rec_train(in,hn,on,inputFeatures,label);
			}
	}
void crosstrain(InputNode in[], HiddenNode hn[], OutputNode on[], float inputFeatures[nOfSamples][nOfFeatures], int labels[])
{
	//scelta random degli indici
	int temp = 0;
	char buffer[100];
	char *newline = "\n\r";
	char *tab = "\t";

	int indexNoTrain[sampleToAvoid * 2] = { 0 };

				bool indexAlreadyPresent = false;

				for (int irand = 0; irand < sampleToAvoid; irand++)
				{
					temp = rand() % 50;
					for (int i = 0; i < irand; i++)
					{
						if (temp != indexNoTrain[i])
						{
							indexAlreadyPresent = false;
						}
						else
						{
							indexAlreadyPresent = true;
							break;
						}
					}
					if (!indexAlreadyPresent)
						indexNoTrain[irand] = temp;
					else
						irand--;
				}
				indexAlreadyPresent = false;
				for (int irand = 0; irand < sampleToAvoid; irand++)
				{
					temp = (rand() % 50) + 50;
					for (int i = 0; i < irand; i++)
					{
						if (temp != indexNoTrain[i + sampleToAvoid])
						{
							indexAlreadyPresent = false;
						}
						else
						{
							indexAlreadyPresent = true;
							break;
						}
					}
					if (!indexAlreadyPresent)
						indexNoTrain[irand + sampleToAvoid] = temp;
					else
						irand--;
				}
				//ordinamento degli indici per semplicità in fase di training
				for (int i = 0; i <sampleToAvoid*2; i++)
				{
					for (int j = 0; j < sampleToAvoid*2; j++)
					{
						if (indexNoTrain[j] > indexNoTrain[i])
						{
							int tmp = indexNoTrain[i];
							indexNoTrain[i] = indexNoTrain[j];
							indexNoTrain[j] = tmp;
						}
					}
				}

				//debug verifica degli indici
				for(int i =0;i<sampleToAvoid*2;i++)
				{
					snprintf(buffer, sizeof buffer, "%i", indexNoTrain[i]);
					HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer), 0xFFFF);
					HAL_UART_Transmit(&huart2, (uint8_t*) newline, strlen(newline), 0xFFFF);
				}

				int c1 = 0;
				int c2 = sampleToAvoid;
				//training che evita gli indici esclusi
				for (int i = 0; i < nOfSamples / 2; i++)
				{
					bool train_index = true;
					if (indexNoTrain[c1] == i)
					{
						c1++;
						train_index = false;
					}
					if (train_index)
					{
						rec_train(in, hn, on, inputFeatures[i], labels[i]);
					}
					train_index = true;
					if (indexNoTrain[c2] == i + nOfSamples / 2)
					{
						c2++;
						train_index = false;
					}
					if (train_index)
					{
						rec_train(in, hn, on, inputFeatures[i + nOfSamples / 2], labels[i + nOfSamples / 2]);
					}
					train_index = true;
				}
				//verifico l'etichetta dei 15+15 vettori esclusi (test set)
				int ct_labels[sampleToAvoid*2]={0};
				int tmp_ind;
				for (int i = 0;i<sampleToAvoid*2;i++)
				{
					tmp_ind=indexNoTrain[i];
					ct_labels[i]=calculateSampleLabel(in,hn,on,inputFeatures[tmp_ind]);
				}
				//stampa i valori
				for (int i = 0;i<sampleToAvoid*2;i++)
				{
					snprintf(buffer, sizeof buffer, "%i", ct_labels[i]);
					HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer), 0xFFFF);
					HAL_UART_Transmit(&huart2, (uint8_t*) newline, strlen(newline), 0xFFFF);
			}
	}
//generazione di valori random tra -0.5 e 0.5 utilizzata per bias e pesi
float generateRandomWeights()
{
	float result = 0;
	result = (float)(rand() % 1000);
	result = result - 500;
	result = result / 1000;
	return result;
}
//serve a stampare su console la rete, genera quello che è l'argomento della funzione loadNetwork
void printNetwork(InputNode in[], HiddenNode hn[], OutputNode on[])
{
	//int index = 0;

	float temp=0;
	char *first ="in[";
	char *second="].weights[";
	char *third="]=";
	char *last=";";
	char *newline="\n\r";
	char buffer[100];

	//pesi tra nodi input e hidden
	for (int i = 0; i < nOfFeatures; i++)
	{
		/*
		printf("#Nodo input ");
		printf("%i", i);
		printf(": \n");
		*/

		for (int h = 0; h < nOfHiddenNodes; h++)
		{
			//printf("in[");
			//printf("%i", i);
			//printf("].weights[");
			//printf("%i", h);
			//printf("]= ");

			//printf("%.9f", weights[index]);

			//printf(";\n");

			//printf("\n");

			HAL_UART_Transmit(&huart2, (uint8_t*) first, strlen(first), 0xFFFF);
			snprintf(buffer, sizeof buffer, "%i", i);
			HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer),0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*) second, strlen(second), 0xFFFF);
			snprintf(buffer, sizeof buffer, "%i", h);
			HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer),0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*) third, strlen(third), 0xFFFF);
			temp=in[i].weights[h];
			snprintf(buffer, sizeof buffer, "%f", temp);
			HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer),0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*) last, strlen(last), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*) newline, strlen(newline), 0xFFFF);
		}
	}
	//pesi tra nodi hidden e output
	for (int h = 0; h < nOfHiddenNodes; h++)
	{
		/*
		printf("#Nodo hidden ");
		printf("%i", h);
		printf(": \n");
		*/
		for (int o = 0; o < nOfOutputNodes; o++)
		{
			//printf("hn[");
			//printf("%i", h);
			//printf("].weights[");
			//printf("%i", o);
			//printf("]= ");

			//printf("%.9f", weights[index]);

			//printf(";\n");

			//printf("\n");
			first="hn[";

			HAL_UART_Transmit(&huart2, (uint8_t*) first, strlen(first), 0xFFFF);
			snprintf(buffer, sizeof buffer, "%i", h);
			HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer),0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*) second, strlen(second), 0xFFFF);
			snprintf(buffer, sizeof buffer, "%i", o);
			HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer),0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*) third, strlen(third), 0xFFFF);
			temp=hn[h].weights[o];
			snprintf(buffer, sizeof buffer, "%f", temp);
			HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer),0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*) last, strlen(last), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*) newline, strlen(newline), 0xFFFF);
		}
	}
	//bias nodi hidden
	for (int h = 0; h < nOfHiddenNodes; h++)
	{
		//printf("hn[");
		//printf("%i", h);
		//printf("].bias");
		//printf("= ");

		//printf("%.9f", biases[index]);

		//printf(";\n");

		//printf("\n");
		HAL_UART_Transmit(&huart2, (uint8_t*) first, strlen(first), 0xFFFF);
		snprintf(buffer, sizeof buffer, "%i", h);
		HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer),0xFFFF);
		second="].bias=";
		HAL_UART_Transmit(&huart2, (uint8_t*) second, strlen(second), 0xFFFF);
		temp=hn[h].bias;
		snprintf(buffer, sizeof buffer, "%f", temp);
		HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer),0xFFFF);
		HAL_UART_Transmit(&huart2, (uint8_t*) last, strlen(last), 0xFFFF);
		HAL_UART_Transmit(&huart2, (uint8_t*) newline, strlen(newline), 0xFFFF);
	}
	//printf("#Bias nodi(o) output:\n");
	//bias nodi output
	for (int o = 0; o < nOfOutputNodes; o++)
	{
		//printf("on[");
		//printf("%i", o);
		//printf("].bias");
		//printf("= ");

		//printf("%.9f", biases[index]);
		//printf(";\n");
		//printf("\n");
		//index++;
		first="on[";
		HAL_UART_Transmit(&huart2, (uint8_t*) first, strlen(first), 0xFFFF);
		snprintf(buffer, sizeof buffer, "%i", o);
		HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer),0xFFFF);
		HAL_UART_Transmit(&huart2, (uint8_t*) second, strlen(second), 0xFFFF);
		temp=on[o].bias;
		snprintf(buffer, sizeof buffer, "%f", temp);
		HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer),0xFFFF);
		HAL_UART_Transmit(&huart2, (uint8_t*) last, strlen(last), 0xFFFF);
		HAL_UART_Transmit(&huart2, (uint8_t*) newline, strlen(newline), 0xFFFF);
	}
}
//nel caso in cui il training set occupi troppo spazio
void loadTrainedNetwork(InputNode in[], HiddenNode hn[], OutputNode on[])
{
	in[0].weights[0]=0.356179;
	in[0].weights[1]=0.079830;
	in[0].weights[2]=-0.275275;
	in[0].weights[3]=-0.394161;
	in[0].weights[4]=-0.270430;
	in[0].weights[5]=-0.239110;
	in[0].weights[6]=-0.458076;
	in[0].weights[7]=0.362049;
	in[0].weights[8]=0.109235;
	in[0].weights[9]=0.078153;
	in[0].weights[10]=0.259249;
	in[0].weights[11]=0.088486;
	in[0].weights[12]=0.294910;
	in[0].weights[13]=-0.251228;
	in[0].weights[14]=0.630161;
	in[0].weights[15]=-0.336279;
	in[0].weights[16]=-0.294884;
	in[0].weights[17]=0.095464;
	in[0].weights[18]=0.485024;
	in[0].weights[19]=-0.040717;
	in[0].weights[20]=0.056691;
	in[0].weights[21]=0.283034;
	in[0].weights[22]=0.204336;
	in[0].weights[23]=-0.047275;
	in[0].weights[24]=-0.219970;
	in[0].weights[25]=0.225574;
	in[0].weights[26]=-0.151010;
	in[0].weights[27]=0.405041;
	in[0].weights[28]=-0.060781;
	in[0].weights[29]=0.197263;
	in[1].weights[0]=0.494354;
	in[1].weights[1]=-0.064714;
	in[1].weights[2]=-0.358175;
	in[1].weights[3]=0.240151;
	in[1].weights[4]=-0.228639;
	in[1].weights[5]=-0.108284;
	in[1].weights[6]=-0.535278;
	in[1].weights[7]=0.323805;
	in[1].weights[8]=-0.074381;
	in[1].weights[9]=-0.371049;
	in[1].weights[10]=-0.125576;
	in[1].weights[11]=-0.336910;
	in[1].weights[12]=0.203597;
	in[1].weights[13]=0.163451;
	in[1].weights[14]=0.239151;
	in[1].weights[15]=0.602093;
	in[1].weights[16]=-0.138834;
	in[1].weights[17]=-0.325683;
	in[1].weights[18]=-0.225787;
	in[1].weights[19]=0.117534;
	in[1].weights[20]=0.185210;
	in[1].weights[21]=0.251437;
	in[1].weights[22]=0.297626;
	in[1].weights[23]=0.219492;
	in[1].weights[24]=-0.088664;
	in[1].weights[25]=0.092669;
	in[1].weights[26]=0.220292;
	in[1].weights[27]=0.003039;
	in[1].weights[28]=0.070144;
	in[1].weights[29]=0.279962;
	in[2].weights[0]=0.245655;
	in[2].weights[1]=0.204925;
	in[2].weights[2]=-0.038552;
	in[2].weights[3]=-0.287033;
	in[2].weights[4]=-0.038630;
	in[2].weights[5]=0.133625;
	in[2].weights[6]=-0.305868;
	in[2].weights[7]=0.285294;
	in[2].weights[8]=-0.208608;
	in[2].weights[9]=-0.249259;
	in[2].weights[10]=-0.173537;
	in[2].weights[11]=0.363070;
	in[2].weights[12]=0.082519;
	in[2].weights[13]=-0.308168;
	in[2].weights[14]=0.384349;
	in[2].weights[15]=0.375951;
	in[2].weights[16]=-0.064509;
	in[2].weights[17]=-0.630458;
	in[2].weights[18]=0.317069;
	in[2].weights[19]=0.351661;
	in[2].weights[20]=-0.523641;
	in[2].weights[21]=-0.276591;
	in[2].weights[22]=-0.183754;
	in[2].weights[23]=-0.366903;
	in[2].weights[24]=-0.490725;
	in[2].weights[25]=-0.150780;
	in[2].weights[26]=-0.164889;
	in[2].weights[27]=0.216319;
	in[2].weights[28]=0.678532;
	in[2].weights[29]=0.049410;
	in[3].weights[0]=0.283662;
	in[3].weights[1]=0.431332;
	in[3].weights[2]=0.068489;
	in[3].weights[3]=0.347900;
	in[3].weights[4]=0.005846;
	in[3].weights[5]=-0.448490;
	in[3].weights[6]=0.242256;
	in[3].weights[7]=-0.172291;
	in[3].weights[8]=0.113719;
	in[3].weights[9]=-0.198809;
	in[3].weights[10]=-0.302561;
	in[3].weights[11]=0.138995;
	in[3].weights[12]=0.455533;
	in[3].weights[13]=0.055108;
	in[3].weights[14]=0.414130;
	in[3].weights[15]=0.191130;
	in[3].weights[16]=-0.302797;
	in[3].weights[17]=0.348094;
	in[3].weights[18]=0.078940;
	in[3].weights[19]=-0.040113;
	in[3].weights[20]=-0.538938;
	in[3].weights[21]=0.369447;
	in[3].weights[22]=0.360639;
	in[3].weights[23]=-0.402769;
	in[3].weights[24]=0.423277;
	in[3].weights[25]=0.001239;
	in[3].weights[26]=-0.461697;
	in[3].weights[27]=-0.295343;
	in[3].weights[28]=-0.067208;
	in[3].weights[29]=-0.325520;
	in[4].weights[0]=0.274448;
	in[4].weights[1]=-0.413356;
	in[4].weights[2]=0.480500;
	in[4].weights[3]=0.295510;
	in[4].weights[4]=0.373276;
	in[4].weights[5]=-0.021228;
	in[4].weights[6]=0.480013;
	in[4].weights[7]=-0.349885;
	in[4].weights[8]=0.401101;
	in[4].weights[9]=-0.409053;
	in[4].weights[10]=0.404496;
	in[4].weights[11]=-0.057150;
	in[4].weights[12]=-0.391485;
	in[4].weights[13]=0.120367;
	in[4].weights[14]=-0.345323;
	in[4].weights[15]=-0.296105;
	in[4].weights[16]=0.227781;
	in[4].weights[17]=0.313528;
	in[4].weights[18]=-0.015210;
	in[4].weights[19]=-0.052863;
	in[4].weights[20]=-0.118712;
	in[4].weights[21]=-0.023125;
	in[4].weights[22]=-0.053073;
	in[4].weights[23]=-0.495426;
	in[4].weights[24]=0.174972;
	in[4].weights[25]=-0.125406;
	in[4].weights[26]=0.565506;
	in[4].weights[27]=0.283758;
	in[4].weights[28]=0.053589;
	in[4].weights[29]=0.421452;
	in[5].weights[0]=-0.367952;
	in[5].weights[1]=0.200124;
	in[5].weights[2]=0.342423;
	in[5].weights[3]=0.048766;
	in[5].weights[4]=-0.341378;
	in[5].weights[5]=-0.353880;
	in[5].weights[6]=0.095298;
	in[5].weights[7]=-0.601944;
	in[5].weights[8]=0.143400;
	in[5].weights[9]=0.330911;
	in[5].weights[10]=0.442978;
	in[5].weights[11]=-0.315265;
	in[5].weights[12]=-0.035283;
	in[5].weights[13]=-0.146576;
	in[5].weights[14]=-0.038851;
	in[5].weights[15]=0.446205;
	in[5].weights[16]=-0.606152;
	in[5].weights[17]=-0.083125;
	in[5].weights[18]=-0.239952;
	in[5].weights[19]=0.367239;
	in[5].weights[20]=0.023091;
	in[5].weights[21]=0.186400;
	in[5].weights[22]=-0.304797;
	in[5].weights[23]=-0.235413;
	in[5].weights[24]=-0.083181;
	in[5].weights[25]=-0.131967;
	in[5].weights[26]=-0.317685;
	in[5].weights[27]=0.025353;
	in[5].weights[28]=0.469743;
	in[5].weights[29]=0.278506;
	in[6].weights[0]=-0.363788;
	in[6].weights[1]=-0.200548;
	in[6].weights[2]=0.938652;
	in[6].weights[3]=0.799529;
	in[6].weights[4]=0.007861;
	in[6].weights[5]=0.742456;
	in[6].weights[6]=0.281356;
	in[6].weights[7]=0.514911;
	in[6].weights[8]=-0.591011;
	in[6].weights[9]=-0.586168;
	in[6].weights[10]=-0.788896;
	in[6].weights[11]=0.229834;
	in[6].weights[12]=-1.085829;
	in[6].weights[13]=0.091660;
	in[6].weights[14]=-1.006862;
	in[6].weights[15]=-0.164335;
	in[6].weights[16]=0.249604;
	in[6].weights[17]=1.094530;
	in[6].weights[18]=0.146165;
	in[6].weights[19]=-1.573275;
	in[6].weights[20]=0.008178;
	in[6].weights[21]=-0.419955;
	in[6].weights[22]=-0.851854;
	in[6].weights[23]=-0.131268;
	in[6].weights[24]=0.071710;
	in[6].weights[25]=0.779246;
	in[6].weights[26]=1.129456;
	in[6].weights[27]=0.010866;
	in[6].weights[28]=-0.781081;
	in[6].weights[29]=-0.234829;
	in[7].weights[0]=-0.394077;
	in[7].weights[1]=0.141331;
	in[7].weights[2]=0.034788;
	in[7].weights[3]=0.207800;
	in[7].weights[4]=0.103488;
	in[7].weights[5]=0.455823;
	in[7].weights[6]=0.842488;
	in[7].weights[7]=0.295348;
	in[7].weights[8]=-0.606170;
	in[7].weights[9]=-0.305199;
	in[7].weights[10]=-0.608814;
	in[7].weights[11]=-0.131505;
	in[7].weights[12]=-0.026769;
	in[7].weights[13]=-0.138992;
	in[7].weights[14]=-0.720686;
	in[7].weights[15]=-0.486258;
	in[7].weights[16]=0.093595;
	in[7].weights[17]=0.715174;
	in[7].weights[18]=0.050224;
	in[7].weights[19]=-0.831878;
	in[7].weights[20]=0.520965;
	in[7].weights[21]=-0.182653;
	in[7].weights[22]=-0.568930;
	in[7].weights[23]=-0.565566;
	in[7].weights[24]=-0.163067;
	in[7].weights[25]=-0.277141;
	in[7].weights[26]=0.785304;
	in[7].weights[27]=0.315442;
	in[7].weights[28]=-0.578539;
	in[7].weights[29]=-0.282510;
	in[8].weights[0]=-1.032842;
	in[8].weights[1]=0.270710;
	in[8].weights[2]=0.430772;
	in[8].weights[3]=0.901960;
	in[8].weights[4]=-0.678803;
	in[8].weights[5]=0.705578;
	in[8].weights[6]=0.938297;
	in[8].weights[7]=0.578332;
	in[8].weights[8]=-0.413482;
	in[8].weights[9]=-0.266991;
	in[8].weights[10]=-0.284738;
	in[8].weights[11]=0.565564;
	in[8].weights[12]=-1.030864;
	in[8].weights[13]=0.388503;
	in[8].weights[14]=-1.144371;
	in[8].weights[15]=-0.771287;
	in[8].weights[16]=0.805790;
	in[8].weights[17]=1.037907;
	in[8].weights[18]=-0.526516;
	in[8].weights[19]=-1.309937;
	in[8].weights[20]=-0.062404;
	in[8].weights[21]=-0.065925;
	in[8].weights[22]=-0.198945;
	in[8].weights[23]=-0.493315;
	in[8].weights[24]=-0.395651;
	in[8].weights[25]=-0.067255;
	in[8].weights[26]=0.398037;
	in[8].weights[27]=-0.001868;
	in[8].weights[28]=-0.944669;
	in[8].weights[29]=-0.327186;
	in[9].weights[0]=-0.483097;
	in[9].weights[1]=0.296225;
	in[9].weights[2]=0.367978;
	in[9].weights[3]=0.427484;
	in[9].weights[4]=-0.046008;
	in[9].weights[5]=0.239648;
	in[9].weights[6]=-0.008413;
	in[9].weights[7]=0.602560;
	in[9].weights[8]=-0.399114;
	in[9].weights[9]=-0.115975;
	in[9].weights[10]=-0.536590;
	in[9].weights[11]=-0.071771;
	in[9].weights[12]=0.207155;
	in[9].weights[13]=-0.416833;
	in[9].weights[14]=-0.576562;
	in[9].weights[15]=-0.429730;
	in[9].weights[16]=0.668933;
	in[9].weights[17]=0.214848;
	in[9].weights[18]=0.445998;
	in[9].weights[19]=-0.406410;
	in[9].weights[20]=0.110683;
	in[9].weights[21]=-0.325261;
	in[9].weights[22]=-0.113297;
	in[9].weights[23]=0.125131;
	in[9].weights[24]=-0.324884;
	in[9].weights[25]=0.086674;
	in[9].weights[26]=0.071008;
	in[9].weights[27]=-0.472481;
	in[9].weights[28]=-0.563489;
	in[9].weights[29]=-0.380148;
	in[10].weights[0]=0.505146;
	in[10].weights[1]=0.414382;
	in[10].weights[2]=-0.491624;
	in[10].weights[3]=0.053054;
	in[10].weights[4]=-0.440889;
	in[10].weights[5]=0.243467;
	in[10].weights[6]=-0.486385;
	in[10].weights[7]=-0.128016;
	in[10].weights[8]=-0.155756;
	in[10].weights[9]=-0.349709;
	in[10].weights[10]=0.209246;
	in[10].weights[11]=-0.484380;
	in[10].weights[12]=0.175670;
	in[10].weights[13]=0.321943;
	in[10].weights[14]=0.574218;
	in[10].weights[15]=0.371705;
	in[10].weights[16]=0.236886;
	in[10].weights[17]=0.275831;
	in[10].weights[18]=-0.233939;
	in[10].weights[19]=0.590428;
	in[10].weights[20]=-0.484281;
	in[10].weights[21]=-0.436022;
	in[10].weights[22]=0.173500;
	in[10].weights[23]=-0.313162;
	in[10].weights[24]=-0.487379;
	in[10].weights[25]=-0.058388;
	in[10].weights[26]=-0.280915;
	in[10].weights[27]=-0.121212;
	in[10].weights[28]=0.004141;
	in[10].weights[29]=0.203114;
	in[11].weights[0]=0.076863;
	in[11].weights[1]=-0.178005;
	in[11].weights[2]=-0.152193;
	in[11].weights[3]=-0.546050;
	in[11].weights[4]=0.417873;
	in[11].weights[5]=-0.445080;
	in[11].weights[6]=-0.367776;
	in[11].weights[7]=-0.422614;
	in[11].weights[8]=0.122107;
	in[11].weights[9]=-0.308299;
	in[11].weights[10]=-0.145915;
	in[11].weights[11]=-0.058954;
	in[11].weights[12]=0.575712;
	in[11].weights[13]=-0.067644;
	in[11].weights[14]=-0.260556;
	in[11].weights[15]=0.016465;
	in[11].weights[16]=-0.213284;
	in[11].weights[17]=-0.046233;
	in[11].weights[18]=-0.439033;
	in[11].weights[19]=0.525481;
	in[11].weights[20]=0.260384;
	in[11].weights[21]=-0.394250;
	in[11].weights[22]=0.527747;
	in[11].weights[23]=0.035008;
	in[11].weights[24]=0.060209;
	in[11].weights[25]=0.394088;
	in[11].weights[26]=-0.105717;
	in[11].weights[27]=-0.366471;
	in[11].weights[28]=0.128838;
	in[11].weights[29]=0.122014;
	in[12].weights[0]=-0.156747;
	in[12].weights[1]=0.419842;
	in[12].weights[2]=0.116998;
	in[12].weights[3]=0.159139;
	in[12].weights[4]=-0.217625;
	in[12].weights[5]=-0.201302;
	in[12].weights[6]=-0.311185;
	in[12].weights[7]=0.338552;
	in[12].weights[8]=0.329941;
	in[12].weights[9]=-0.012920;
	in[12].weights[10]=-0.102245;
	in[12].weights[11]=-0.264846;
	in[12].weights[12]=-0.051219;
	in[12].weights[13]=-0.229918;
	in[12].weights[14]=-0.026521;
	in[12].weights[15]=-0.376698;
	in[12].weights[16]=0.176786;
	in[12].weights[17]=0.275219;
	in[12].weights[18]=0.256231;
	in[12].weights[19]=-0.252915;
	in[12].weights[20]=0.355370;
	in[12].weights[21]=-0.250472;
	in[12].weights[22]=-0.097027;
	in[12].weights[23]=-0.067708;
	in[12].weights[24]=-0.199532;
	in[12].weights[25]=0.122850;
	in[12].weights[26]=0.048089;
	in[12].weights[27]=0.267603;
	in[12].weights[28]=0.288453;
	in[12].weights[29]=0.405761;
	in[13].weights[0]=0.293487;
	in[13].weights[1]=0.366524;
	in[13].weights[2]=-0.110790;
	in[13].weights[3]=-0.048158;
	in[13].weights[4]=-0.157557;
	in[13].weights[5]=0.241042;
	in[13].weights[6]=0.099537;
	in[13].weights[7]=0.207303;
	in[13].weights[8]=-0.311405;
	in[13].weights[9]=0.325121;
	in[13].weights[10]=-0.216152;
	in[13].weights[11]=0.303288;
	in[13].weights[12]=-0.023167;
	in[13].weights[13]=-0.066306;
	in[13].weights[14]=0.261636;
	in[13].weights[15]=-0.330657;
	in[13].weights[16]=0.103113;
	in[13].weights[17]=-0.385256;
	in[13].weights[18]=0.300212;
	in[13].weights[19]=0.106565;
	in[13].weights[20]=0.454331;
	in[13].weights[21]=-0.419717;
	in[13].weights[22]=-0.255784;
	in[13].weights[23]=-0.204291;
	in[13].weights[24]=0.281790;
	in[13].weights[25]=-0.399583;
	in[13].weights[26]=-0.085998;
	in[13].weights[27]=-0.068869;
	in[13].weights[28]=-0.127823;
	in[13].weights[29]=-0.166447;
	in[14].weights[0]=-0.200440;
	in[14].weights[1]=0.330647;
	in[14].weights[2]=0.214185;
	in[14].weights[3]=-0.012956;
	in[14].weights[4]=0.373058;
	in[14].weights[5]=0.101574;
	in[14].weights[6]=0.058504;
	in[14].weights[7]=-0.434412;
	in[14].weights[8]=-0.104703;
	in[14].weights[9]=0.123552;
	in[14].weights[10]=-0.219993;
	in[14].weights[11]=-0.403259;
	in[14].weights[12]=-0.123677;
	in[14].weights[13]=0.195531;
	in[14].weights[14]=-0.148187;
	in[14].weights[15]=-0.201370;
	in[14].weights[16]=-0.048147;
	in[14].weights[17]=0.088435;
	in[14].weights[18]=0.272929;
	in[14].weights[19]=0.062583;
	in[14].weights[20]=0.327721;
	in[14].weights[21]=0.343651;
	in[14].weights[22]=0.408943;
	in[14].weights[23]=-0.141292;
	in[14].weights[24]=-0.193153;
	in[14].weights[25]=0.106086;
	in[14].weights[26]=-0.201124;
	in[14].weights[27]=0.316007;
	in[14].weights[28]=-0.189099;
	in[14].weights[29]=-0.323014;
	hn[0].weights[0]=1.239107;
	hn[1].weights[0]=0.088112;
	hn[2].weights[0]=-1.099220;
	hn[3].weights[0]=-1.189886;
	hn[4].weights[0]=0.383850;
	hn[5].weights[0]=-1.301010;
	hn[6].weights[0]=-1.289747;
	hn[7].weights[0]=-0.898556;
	hn[8].weights[0]=0.841663;
	hn[9].weights[0]=0.628173;
	hn[10].weights[0]=0.886356;
	hn[11].weights[0]=-0.519564;
	hn[12].weights[0]=1.412227;
	hn[13].weights[0]=-0.191822;
	hn[14].weights[0]=1.941387;
	hn[15].weights[0]=0.947538;
	hn[16].weights[0]=-1.043311;
	hn[17].weights[0]=-1.684435;
	hn[18].weights[0]=0.156335;
	hn[19].weights[0]=2.539948;
	hn[20].weights[0]=-0.310550;
	hn[21].weights[0]=0.335641;
	hn[22].weights[0]=1.054412;
	hn[23].weights[0]=0.726303;
	hn[24].weights[0]=0.164308;
	hn[25].weights[0]=-0.431875;
	hn[26].weights[0]=-1.427690;
	hn[27].weights[0]=0.164163;
	hn[28].weights[0]=1.466539;
	hn[29].weights[0]=0.727638;
	hn[0].bias=0.051778;
	hn[1].bias=0.019616;
	hn[2].bias=-0.029910;
	hn[3].bias=-0.065487;
	hn[4].bias=0.004201;
	hn[5].bias=-0.269944;
	hn[6].bias=-0.055023;
	hn[7].bias=-0.109744;
	hn[8].bias=0.156608;
	hn[9].bias=0.061697;
	hn[10].bias=0.151709;
	hn[11].bias=-0.044247;
	hn[12].bias=0.110151;
	hn[13].bias=-0.007923;
	hn[14].bias=0.306844;
	hn[15].bias=-0.015466;
	hn[16].bias=-0.080659;
	hn[17].bias=-0.116967;
	hn[18].bias=-0.008890;
	hn[19].bias=0.555380;
	hn[20].bias=-0.047929;
	hn[21].bias=-0.000106;
	hn[22].bias=0.086427;
	hn[23].bias=0.062389;
	hn[24].bias=-0.004270;
	hn[25].bias=-0.025090;
	hn[26].bias=-0.136879;
	hn[27].bias=0.003560;
	hn[28].bias=0.148718;
	hn[29].bias=0.047528;
	on[0].bias=-0.000155;
}
