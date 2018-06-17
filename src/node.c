/*
 * node.c
 *      Author: andre
 */
#include "node.h"

//funzione sigmoide utilizzata per il calcolo del valore del nodo
double sigmoid(double x)
{
	return tanh(x);
}
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
	float hSigmoidValues[nOfHiddenNodes] = { 0 };

	float oValues[nOfOutputNodes] = { 0 };
	/*
	for (int h = 0; h < nOfHiddenNodes; h++)//per ogni nodo del primo livello
	{
		for (int i = 0; i < nOfFeatures; i++)//per ogni nodo del livello hidden
		{
			values[h] = 0;
			values[h] = values[h] + in[i].value*in[i].weights[h];
			//temp = in[i].value;
			//temp = temp + in[i].value*in[i].weights[h];
			//temp = temp + hn[h].value;
			//temp = temp + in[i].bias; //nuovo
			//temp = 0;

			/////values[h] = values[h] + (in[i].value*in[i].weights[h]);
		}
		//hn[h].value = temp;
		//temp = 0;
	}
	*/
	for (int h = 0; h < nOfHiddenNodes; h++)
	{
		//bias dello specifico nodo hidden
		hValues[h] = hn[h].bias;
		for (int i = 0; i < nOfFeatures; i++)
		{
			//calcolo dell'argomento della funzione di attivazione come somma dei prodotti in*peso
			hValues[h] = hValues[h] + (in[i].value*in[i].weights[h]);

			//applicazione della funzione di attivazione
			hSigmoidValues[h]= fsigmoid(hValues[h]);
			hn[h].value = fsigmoid(hValues[h]);
		}
	}
	//int placeholder = 0;
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
	int placeholder2 = 0;


	//va ora applicata la sigmoide ai valori dei nodi hidden
	/*
	for (int h = 0; h < nOfHiddenNodes; h++)
	{
		hn[h].value = fsigmoid(hn[h].value);
	}
	*/
	//ora si propaga da hidden a output
	/*
	for (int h = 0; h < nOfHiddenNodes; h++)//per ogni nodo del livello hidden
	{
		for (int o = 0; o < nOfOutputNodes; o++)//per ogni nodo del livello out
		{
			/*
			temp = hn[h].value;
			temp = temp*hn[h].weights[o];
			//temp = temp + on[o].value;
			temp = temp + hn[h].bias;
			on[o].value = temp;
			temp = 0;

		}
	}
	*/
	//va ora applicata la sigmoide ai valori dei nodi out
	/*
	for (int o = 0; o < nOfOutputNodes; o++)
	{
		on[o].value = fsigmoid(on[o].value);
	}
	*/
}
int calculateOutput(InputNode in[], HiddenNode hn[], OutputNode on[], float inputFeatures[])
{
	for (int i = 0; i < nOfFeatures; i++)
	{
		in[i].value = inputFeatures[i];
	}
	feedForward(in, hn, on);
	float result = on[0].value;
	if (on[0].value >= 0.5)
	{
		return 1;
	}
	else
	{
		return 0;
	}
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
//nel caso in cui il training set occupi troppo spazio
void loadTrainedNetwork(InputNode in[], HiddenNode hn[], OutputNode on[])
{
	in[0].weights[0] = 0.298679918;
	in[0].weights[1] = 0.233234644;
	in[0].weights[2] = -0.499638140;
	in[0].weights[3] = -0.032317653;
	in[0].weights[4] = -0.364448339;
	in[0].weights[5] = -0.078550749;
	in[0].weights[6] = 0.053459961;
	in[0].weights[7] = 0.207665265;
	in[0].weights[8] = -0.433739692;
	in[0].weights[9] = 0.390439838;
	in[0].weights[10] = 0.159987882;
	in[0].weights[11] = -0.238242850;
	in[0].weights[12] = -0.012882762;
	in[0].weights[13] = -0.099238135;
	in[0].weights[14] = -0.483019859;
	in[0].weights[15] = 0.178416520;
	in[0].weights[16] = -0.177899376;
	in[0].weights[17] = -0.389987439;
	in[0].weights[18] = 0.315950364;
	in[0].weights[19] = -0.473218113;
	in[0].weights[20] = -0.122292295;
	in[0].weights[21] = 0.189441904;
	in[0].weights[22] = -0.057304129;
	in[0].weights[23] = -0.144892231;
	in[0].weights[24] = -0.462774545;
	in[0].weights[25] = -0.467921108;
	in[0].weights[26] = -0.464856625;
	in[0].weights[27] = 0.130442247;
	in[0].weights[28] = -0.362654716;
	in[0].weights[29] = 0.268065631;
	in[1].weights[0] = -0.103383452;
	in[1].weights[1] = 0.632870972;
	in[1].weights[2] = 0.131639749;
	in[1].weights[3] = 0.206356689;
	in[1].weights[4] = -0.103117190;
	in[1].weights[5] = -0.012760320;
	in[1].weights[6] = -0.309541672;
	in[1].weights[7] = 0.111338802;
	in[1].weights[8] = -0.255277187;
	in[1].weights[9] = 0.077877425;
	in[1].weights[10] = -0.168847382;
	in[1].weights[11] = -0.164932102;
	in[1].weights[12] = -0.458533704;
	in[1].weights[13] = 0.151391119;
	in[1].weights[14] = 0.466580242;
	in[1].weights[15] = 0.048460860;
	in[1].weights[16] = -0.000953870;
	in[1].weights[17] = 0.205308616;
	in[1].weights[18] = -0.392794639;
	in[1].weights[19] = -0.286327600;
	in[1].weights[20] = -0.383423269;
	in[1].weights[21] = 0.121520676;
	in[1].weights[22] = 0.135498449;
	in[1].weights[23] = -0.055282123;
	in[1].weights[24] = 0.161460996;
	in[1].weights[25] = 0.315578669;
	in[1].weights[26] = -0.226269811;
	in[1].weights[27] = 0.088356845;
	in[1].weights[28] = -0.215383992;
	in[1].weights[29] = 0.307406247;
	in[2].weights[0] = -0.452082723;
	in[2].weights[1] = 0.563316584;
	in[2].weights[2] = 0.121926151;
	in[2].weights[3] = 0.232446790;
	in[2].weights[4] = 0.275028050;
	in[2].weights[5] = 0.144232720;
	in[2].weights[6] = 0.370244652;
	in[2].weights[7] = 0.485459775;
	in[2].weights[8] = 0.274136633;
	in[2].weights[9] = -0.481837690;
	in[2].weights[10] = -0.025428649;
	in[2].weights[11] = 0.056047738;
	in[2].weights[12] = -0.017020287;
	in[2].weights[13] = -0.265612572;
	in[2].weights[14] = -0.202069551;
	in[2].weights[15] = -0.281805664;
	in[2].weights[16] = -0.170788333;
	in[2].weights[17] = -0.058956891;
	in[2].weights[18] = -0.404003948;
	in[2].weights[19] = 0.151602238;
	in[2].weights[20] = -0.335738301;
	in[2].weights[21] = 0.181543365;
	in[2].weights[22] = 0.080301628;
	in[2].weights[23] = -0.021823702;
	in[2].weights[24] = -0.218096092;
	in[2].weights[25] = -0.159429774;
	in[2].weights[26] = 0.182321504;
	in[2].weights[27] = 0.272455275;
	in[2].weights[28] = 0.002737682;
	in[2].weights[29] = 0.396424353;
	in[3].weights[0] = -0.463637114;
	in[3].weights[1] = -0.344259709;
	in[3].weights[2] = 0.451770812;
	in[3].weights[3] = 0.217126444;
	in[3].weights[4] = -0.276219636;
	in[3].weights[5] = 0.428266466;
	in[3].weights[6] = 0.297734082;
	in[3].weights[7] = -0.229979262;
	in[3].weights[8] = -0.178777203;
	in[3].weights[9] = 0.066535667;
	in[3].weights[10] = -0.010723459;
	in[3].weights[11] = 0.288285077;
	in[3].weights[12] = 0.139169574;
	in[3].weights[13] = 0.038564954;
	in[3].weights[14] = 0.158242315;
	in[3].weights[15] = 0.347001672;
	in[3].weights[16] = 0.141776472;
	in[3].weights[17] = 0.043598603;
	in[3].weights[18] = -0.363562018;
	in[3].weights[19] = 0.036359079;
	in[3].weights[20] = -0.044148710;
	in[3].weights[21] = 0.368984401;
	in[3].weights[22] = 0.060892608;
	in[3].weights[23] = -0.260052562;
	in[3].weights[24] = 0.173930973;
	in[3].weights[25] = -0.309402734;
	in[3].weights[26] = -0.044020280;
	in[3].weights[27] = -0.077673770;
	in[3].weights[28] = -0.097133324;
	in[3].weights[29] = 0.245849729;
	in[4].weights[0] = -0.059993282;
	in[4].weights[1] = 0.048116121;
	in[4].weights[2] = -0.202862546;
	in[4].weights[3] = 0.146287337;
	in[4].weights[4] = -0.187660322;
	in[4].weights[5] = -0.589930058;
	in[4].weights[6] = -0.046291728;
	in[4].weights[7] = 0.303407401;
	in[4].weights[8] = 0.333769679;
	in[4].weights[9] = -0.106057480;
	in[4].weights[10] = 0.069921330;
	in[4].weights[11] = 0.273412436;
	in[4].weights[12] = -0.572667599;
	in[4].weights[13] = -0.379103839;
	in[4].weights[14] = 0.140116662;
	in[4].weights[15] = 0.177572727;
	in[4].weights[16] = 0.144976884;
	in[4].weights[17] = -0.106008291;
	in[4].weights[18] = -0.351609141;
	in[4].weights[19] = 0.476847917;
	in[4].weights[20] = -0.200289518;
	in[4].weights[21] = 0.443282157;
	in[4].weights[22] = 0.087015912;
	in[4].weights[23] = 0.623329937;
	in[4].weights[24] = 0.205900818;
	in[4].weights[25] = -0.174284741;
	in[4].weights[26] = 0.544271111;
	in[4].weights[27] = -0.016290780;
	in[4].weights[28] = 0.000815878;
	in[4].weights[29] = -0.129465327;
	in[5].weights[0] = 0.302817374;
	in[5].weights[1] = 0.359448075;
	in[5].weights[2] = -0.033777896;
	in[5].weights[3] = 0.108742885;
	in[5].weights[4] = -0.134030968;
	in[5].weights[5] = -0.074961275;
	in[5].weights[6] = -0.069505379;
	in[5].weights[7] = -0.213132128;
	in[5].weights[8] = 0.149892673;
	in[5].weights[9] = -0.337291509;
	in[5].weights[10] = 0.028637262;
	in[5].weights[11] = 0.072045892;
	in[5].weights[12] = -0.584293723;
	in[5].weights[13] = 0.282945693;
	in[5].weights[14] = -0.045037355;
	in[5].weights[15] = 0.535842657;
	in[5].weights[16] = -0.226276904;
	in[5].weights[17] = 0.534753978;
	in[5].weights[18] = -0.388193280;
	in[5].weights[19] = 0.002276185;
	in[5].weights[20] = -0.554017663;
	in[5].weights[21] = 0.213875055;
	in[5].weights[22] = -0.011452426;
	in[5].weights[23] = 0.486987889;
	in[5].weights[24] = -0.266950458;
	in[5].weights[25] = -0.455688268;
	in[5].weights[26] = 0.313526362;
	in[5].weights[27] = -0.043477703;
	in[5].weights[28] = 0.225565374;
	in[5].weights[29] = -0.270103842;
	in[6].weights[0] = -0.310734034;
	in[6].weights[1] = -1.358307362;
	in[6].weights[2] = -0.618207216;
	in[6].weights[3] = -0.983397365;
	in[6].weights[4] = 1.123868465;
	in[6].weights[5] = 0.925191641;
	in[6].weights[6] = -0.086195350;
	in[6].weights[7] = -0.156288251;
	in[6].weights[8] = -1.000542879;
	in[6].weights[9] = -0.161364242;
	in[6].weights[10] = -0.103153855;
	in[6].weights[11] = 0.626170874;
	in[6].weights[12] = 0.782140553;
	in[6].weights[13] = -0.549396276;
	in[6].weights[14] = -0.352567792;
	in[6].weights[15] = -0.359080583;
	in[6].weights[16] = -0.432648987;
	in[6].weights[17] = -0.862369239;
	in[6].weights[18] = 0.920904994;
	in[6].weights[19] = 0.410472244;
	in[6].weights[20] = 0.402677953;
	in[6].weights[21] = 0.087390222;
	in[6].weights[22] = -0.156083763;
	in[6].weights[23] = -0.877611220;
	in[6].weights[24] = -0.661381364;
	in[6].weights[25] = 0.515573919;
	in[6].weights[26] = -0.314878404;
	in[6].weights[27] = 0.661427975;
	in[6].weights[28] = -0.372585088;
	in[6].weights[29] = 0.629757643;
	in[7].weights[0] = 0.512139797;
	in[7].weights[1] = -0.888229847;
	in[7].weights[2] = 0.247477293;
	in[7].weights[3] = -0.818851173;
	in[7].weights[4] = 0.204235047;
	in[7].weights[5] = 0.187741622;
	in[7].weights[6] = -0.068377428;
	in[7].weights[7] = 0.309100330;
	in[7].weights[8] = -0.630897760;
	in[7].weights[9] = -0.284093499;
	in[7].weights[10] = -0.135356560;
	in[7].weights[11] = 0.410256594;
	in[7].weights[12] = 0.598914921;
	in[7].weights[13] = -0.596395075;
	in[7].weights[14] = -0.065726683;
	in[7].weights[15] = -0.891050100;
	in[7].weights[16] = -0.576501548;
	in[7].weights[17] = -0.820380986;
	in[7].weights[18] = 0.146643475;
	in[7].weights[19] = -0.001473216;
	in[7].weights[20] = 0.701486349;
	in[7].weights[21] = -0.026652748;
	in[7].weights[22] = -0.075623617;
	in[7].weights[23] = -0.875320494;
	in[7].weights[24] = -0.067461498;
	in[7].weights[25] = -0.034712903;
	in[7].weights[26] = -0.096100524;
	in[7].weights[27] = -0.297278315;
	in[7].weights[28] = -0.131248161;
	in[7].weights[29] = 0.161188200;
	in[8].weights[0] = 0.091989495;
	in[8].weights[1] = -0.106581137;
	in[8].weights[2] = -0.425456047;
	in[8].weights[3] = 0.021589004;
	in[8].weights[4] = 0.456879348;
	in[8].weights[5] = 0.529982150;
	in[8].weights[6] = 0.395375282;
	in[8].weights[7] = -0.095820241;
	in[8].weights[8] = 0.252394915;
	in[8].weights[9] = -0.034014612;
	in[8].weights[10] = -0.440192133;
	in[8].weights[11] = 0.075942226;
	in[8].weights[12] = 0.258185953;
	in[8].weights[13] = -0.002403909;
	in[8].weights[14] = 0.324189603;
	in[8].weights[15] = -0.071003355;
	in[8].weights[16] = 0.446273178;
	in[8].weights[17] = -0.438988119;
	in[8].weights[18] = -0.256372154;
	in[8].weights[19] = 0.266452730;
	in[8].weights[20] = -0.006343003;
	in[8].weights[21] = -0.035766486;
	in[8].weights[22] = 0.289160669;
	in[8].weights[23] = -0.069299109;
	in[8].weights[24] = 0.168638691;
	in[8].weights[25] = -0.341145039;
	in[8].weights[26] = -0.220166966;
	in[8].weights[27] = 0.442091048;
	in[8].weights[28] = -0.188888147;
	in[8].weights[29] = -0.181181028;
	in[9].weights[0] = 0.563266277;
	in[9].weights[1] = -1.273309708;
	in[9].weights[2] = -0.419207931;
	in[9].weights[3] = -1.037397146;
	in[9].weights[4] = 0.469869345;
	in[9].weights[5] = 0.220188946;
	in[9].weights[6] = -0.147196233;
	in[9].weights[7] = -0.557287276;
	in[9].weights[8] = -0.718542337;
	in[9].weights[9] = 0.339632869;
	in[9].weights[10] = -0.906152308;
	in[9].weights[11] = 0.001170957;
	in[9].weights[12] = 0.405138433;
	in[9].weights[13] = 0.108606100;
	in[9].weights[14] = -0.514569223;
	in[9].weights[15] = -0.953081369;
	in[9].weights[16] = -0.023649246;
	in[9].weights[17] = -0.813369155;
	in[9].weights[18] = 1.173904181;
	in[9].weights[19] = -0.254527748;
	in[9].weights[20] = 0.740676403;
	in[9].weights[21] = 0.088390201;
	in[9].weights[22] = 0.754917264;
	in[9].weights[23] = -0.987610877;
	in[9].weights[24] = -0.454378545;
	in[9].weights[25] = 0.522574246;
	in[9].weights[26] = -0.345878303;
	in[9].weights[27] = -0.058568940;
	in[9].weights[28] = -0.703584015;
	in[9].weights[29] = 0.637757421;
	in[10].weights[0] = 0.272137672;
	in[10].weights[1] = -0.998229504;
	in[10].weights[2] = -0.650523365;
	in[10].weights[3] = -0.350852191;
	in[10].weights[4] = 0.378236502;
	in[10].weights[5] = 1.009741306;
	in[10].weights[6] = 0.493621945;
	in[10].weights[7] = 0.209099099;
	in[10].weights[8] = -0.093898408;
	in[10].weights[9] = -0.163093090;
	in[10].weights[10] = -0.201356336;
	in[10].weights[11] = 0.383256644;
	in[10].weights[12] = 0.976914883;
	in[10].weights[13] = 0.088603310;
	in[10].weights[14] = -0.457726240;
	in[10].weights[15] = -0.761049628;
	in[10].weights[16] = -0.413500905;
	in[10].weights[17] = -0.968381226;
	in[10].weights[18] = 0.978642702;
	in[10].weights[19] = 0.268526524;
	in[10].weights[20] = 0.839486539;
	in[10].weights[21] = -0.262652367;
	in[10].weights[22] = -0.018623836;
	in[10].weights[23] = -0.491317838;
	in[10].weights[24] = -0.684461057;
	in[10].weights[25] = -0.096712470;
	in[10].weights[26] = -0.778102398;
	in[10].weights[27] = 0.419721693;
	in[10].weights[28] = -0.473248512;
	in[10].weights[29] = 0.623187304;
	in[11].weights[0] = -0.054010674;
	in[11].weights[1] = 0.023419119;
	in[11].weights[2] = 0.107544065;
	in[11].weights[3] = 0.346589714;
	in[11].weights[4] = -0.150119737;
	in[11].weights[5] = 0.424980849;
	in[11].weights[6] = 0.484375268;
	in[11].weights[7] = -0.197821125;
	in[11].weights[8] = -0.635604680;
	in[11].weights[9] = 0.354984820;
	in[11].weights[10] = -0.231193602;
	in[11].weights[11] = -0.440057784;
	in[11].weights[12] = 0.147186249;
	in[11].weights[13] = -0.313403934;
	in[11].weights[14] = -0.090810254;
	in[11].weights[15] = 0.100996636;
	in[11].weights[16] = 0.133276075;
	in[11].weights[17] = -0.311988205;
	in[11].weights[18] = -0.159372821;
	in[11].weights[19] = 0.021451807;
	in[11].weights[20] = 0.624655664;
	in[11].weights[21] = 0.259233207;
	in[11].weights[22] = 0.115161322;
	in[11].weights[23] = -0.268298388;
	in[11].weights[24] = 0.054638732;
	in[11].weights[25] = 0.141856194;
	in[11].weights[26] = -0.253166646;
	in[11].weights[27] = 0.379091024;
	in[11].weights[28] = 0.279111922;
	in[11].weights[29] = 0.586819708;
	in[12].weights[0] = -0.208343536;
	in[12].weights[1] = -0.355045706;
	in[12].weights[2] = 0.203252912;
	in[12].weights[3] = 0.243439704;
	in[12].weights[4] = -0.169950545;
	in[12].weights[5] = -0.262978017;
	in[12].weights[6] = -0.061001830;
	in[12].weights[7] = -0.080486029;
	in[12].weights[8] = -0.026517166;
	in[12].weights[9] = 0.222292662;
	in[12].weights[10] = -0.423190206;
	in[12].weights[11] = -0.419190317;
	in[12].weights[12] = -0.157450244;
	in[12].weights[13] = -0.132281765;
	in[12].weights[14] = 0.377526999;
	in[12].weights[15] = 0.084352151;
	in[12].weights[16] = -0.094584286;
	in[12].weights[17] = -0.420266628;
	in[12].weights[18] = -0.161231339;
	in[12].weights[19] = 0.386589170;
	in[12].weights[20] = 0.353526384;
	in[12].weights[21] = 0.275294393;
	in[12].weights[22] = 0.493636340;
	in[12].weights[23] = 0.205040216;
	in[12].weights[24] = -0.270714521;
	in[12].weights[25] = -0.249416977;
	in[12].weights[26] = -0.416325420;
	in[12].weights[27] = 0.374832511;
	in[12].weights[28] = -0.109493688;
	in[12].weights[29] = -0.081917062;
	in[13].weights[0] = -0.327163041;
	in[13].weights[1] = 0.049377833;
	in[13].weights[2] = 0.400851429;
	in[13].weights[3] = -0.128908157;
	in[13].weights[4] = -0.219474450;
	in[13].weights[5] = -0.178863779;
	in[13].weights[6] = 0.052775797;
	in[13].weights[7] = 0.124659956;
	in[13].weights[8] = -0.109049037;
	in[13].weights[9] = -0.106523447;
	in[13].weights[10] = -0.332614779;
	in[13].weights[11] = 0.466283232;
	in[13].weights[12] = -0.054608338;
	in[13].weights[13] = 0.273882091;
	in[13].weights[14] = 0.280260265;
	in[13].weights[15] = -0.371694326;
	in[13].weights[16] = -0.271627992;
	in[13].weights[17] = -0.111803941;
	in[13].weights[18] = -0.152288124;
	in[13].weights[19] = 0.111649156;
	in[13].weights[20] = 0.169802830;
	in[13].weights[21] = -0.417619914;
	in[13].weights[22] = -0.052726287;
	in[13].weights[23] = -0.111971982;
	in[13].weights[24] = -0.147417381;
	in[13].weights[25] = -0.060022097;
	in[13].weights[26] = 0.098342665;
	in[13].weights[27] = -0.126946867;
	in[13].weights[28] = 0.256618977;
	in[13].weights[29] = 0.308392853;
	in[14].weights[0] = 0.415110588;
	in[14].weights[1] = -0.396224856;
	in[14].weights[2] = 0.119160220;
	in[14].weights[3] = 0.148387596;
	in[14].weights[4] = 0.085760258;
	in[14].weights[5] = 0.351525247;
	in[14].weights[6] = 0.352579653;
	in[14].weights[7] = 0.477142096;
	in[14].weights[8] = 0.111707859;
	in[14].weights[9] = -0.039481722;
	in[14].weights[10] = -0.341948926;
	in[14].weights[11] = 0.279608727;
	in[14].weights[12] = 0.106807545;
	in[14].weights[13] = -0.292292923;
	in[14].weights[14] = -0.078844875;
	in[14].weights[15] = 0.433007509;
	in[14].weights[16] = -0.479802251;
	in[14].weights[17] = -0.124502026;
	in[14].weights[18] = 0.193311989;
	in[14].weights[19] = 0.080716208;
	in[14].weights[20] = -0.239186078;
	in[14].weights[21] = 0.399363220;
	in[14].weights[22] = 0.289110601;
	in[14].weights[23] = 0.280884653;
	in[14].weights[24] = 0.005417911;
	in[14].weights[25] = -0.267485708;
	in[14].weights[26] = -0.254339546;
	in[14].weights[27] = 0.149530888;
	in[14].weights[28] = 0.416229337;
	in[14].weights[29] = 0.248738945;
	hn[0].weights[0] = -0.471496582;
	hn[1].weights[0] = 2.647963524;
	hn[2].weights[0] = 0.735710025;
	hn[3].weights[0] = 1.585974813;
	hn[4].weights[0] = -1.284258723;
	hn[5].weights[0] = -1.518894315;
	hn[6].weights[0] = -0.248025984;
	hn[7].weights[0] = 0.200609997;
	hn[8].weights[0] = 1.444005370;
	hn[9].weights[0] = -0.034713108;
	hn[10].weights[0] = 0.924279273;
	hn[11].weights[0] = -0.498397797;
	hn[12].weights[0] = -1.598838449;
	hn[13].weights[0] = 0.497636259;
	hn[14].weights[0] = 0.608812153;
	hn[15].weights[0] = 1.423295021;
	hn[16].weights[0] = 0.592789769;
	hn[17].weights[0] = 2.198136806;
	hn[18].weights[0] = -1.740735650;
	hn[19].weights[0] = -0.177196309;
	hn[20].weights[0] = -1.613554120;
	hn[21].weights[0] = 0.072326086;
	hn[22].weights[0] = -0.444055289;
	hn[23].weights[0] = 1.823976755;
	hn[24].weights[0] = 1.038480997;
	hn[25].weights[0] = -0.489793003;
	hn[26].weights[0] = 1.063783169;
	hn[27].weights[0] = -0.542720318;
	hn[28].weights[0] = 0.767476439;
	hn[29].weights[0] = -1.124861956;
	hn[0].bias = -0.064389415;
	hn[1].bias = 0.743061721;
	hn[2].bias = 0.078234889;
	hn[3].bias = 0.270784050;
	hn[4].bias = -0.167233765;
	hn[5].bias = -0.317133635;
	hn[6].bias = -0.029119516;
	hn[7].bias = -0.016436083;
	hn[8].bias = 0.261424661;
	hn[9].bias = -0.017835239;
	hn[10].bias = 0.072396368;
	hn[11].bias = -0.032868288;
	hn[12].bias = -0.091181792;
	hn[13].bias = -0.001225330;
	hn[14].bias = 0.025523838;
	hn[15].bias = 0.128911346;
	hn[16].bias = 0.033433676;
	hn[17].bias = 0.690389037;
	hn[18].bias = -0.181317255;
	hn[19].bias = -0.029987108;
	hn[20].bias = -0.201787755;
	hn[21].bias = -0.023153871;
	hn[22].bias = -0.009057125;
	hn[23].bias = 0.241171002;
	hn[24].bias = 0.180428118;
	hn[25].bias = -0.010818239;
	hn[26].bias = 0.068628788;
	hn[27].bias = -0.054409750;
	hn[28].bias = 0.027892277;
	hn[29].bias = -0.130726546;
	on[0].bias = -0.000224225;
}
void loadTrainedNetworkFromFile(InputNode in[], HiddenNode hn[], OutputNode on[])
{
	FILE* network = NULL;
	float temp = 0.0;

	network = fopen("network.txt", "a"); //"a" serve per crearlo


	network = fopen("network.txt", "r");
	if (network != NULL)
	{
		/*
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
		*/
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


/*
//questa implementazione suppone che le etichette siano due e il nodo di uscita sia solo uno, (contrariamente a quanto fatto finora) che risulta tuttavia più semplice
*/
/*
void train(InputNode in[], HiddenNode hn[], OutputNode on[], float inputFeatures[], int label)
{
	calculateOutput(in, hn, on, inputFeatures);
	float delta_out = 0;
	float delta_hid = 0;
	float weight_adj_hidden_to_out[nOfHiddenNodes] = {0};

	//per prima cosa vanno sistemati i pesi tra livello hidden e out
	float out = on[0].value;
	delta_out = out;
	//delta_out = delta_out*(label - out); //questa è da dispense
	delta_out = delta_out*(out- label); //questa è video yt nei preferiti
	delta_out = delta_out*(1 - out);

	for (int h = 0; h < nOfHiddenNodes; h++)
	{
		weight_adj_hidden_to_out[h] = learningRate*delta_out*hn[h].value;
	}
	for(int i = 0; i <nOfFeatures; i++)
	{
		for(int h = 0; h <nOfHiddenNodes; h++)
		{
			float weight_adj = 0;
			float delta = delta_out;
			delta = delta*hn[h].value;
			delta = delta*(1 - hn[h].value);
			delta = delta*hn[h].weights[0];

			weight_adj = learningRate;
			weight_adj = weight_adj *delta;
			weight_adj = weight_adj *in[i].value;

			//aggiornamento pesi
			in[i].weights[h] = in[i].weights[h] + weight_adj;
		}
	}
	//aggiornamento pesi tra hidden e out
	for (int h = 0; h < nOfHiddenNodes; h++)
	{
		hn[h].weights[0] = hn[h].weights[0] + weight_adj_hidden_to_out[h];
	}
}
*/
/*
//siccome le etichette sono salvate come '0' e '1' bisogna portarle in maniera tale che siano '-1' e '1'
int convertLabel(int label)
{
	if (label == 0)
		return -1;
	else
		return 1;
}
*/
void train(InputNode in[], HiddenNode hn[], OutputNode on[], float inputFeatures[], int label)
{
	float delta_h[nOfHiddenNodes] = {0};
	float delta_o[nOfOutputNodes] = {0};

	//giusto per verifica, eliminabili
	float bias_hid[nOfHiddenNodes] = { 0 };
	float bias_o[nOfOutputNodes] = {0};

	float weight_adj_hid[nOfHiddenNodes] = { 0 };

	float error=0;
	calculateOutput(in, hn, on, inputFeatures);

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
	int placeholderrr = 0;
	//aggiornamento pesi input-hidden layer
	for (int h = 0; h < nOfHiddenNodes; h++)
	{
		//giusto per verifica
		bias_hid[h] = learningRate*delta_h[h];
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
	int placeholderz = 0;
	for (int o = 0; o < nOfOutputNodes; o++)
	{
		bias_o[o] = learningRate*delta_o[o];
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
	calculateOutput(in, hn, on, inputFeatures);
	error=(fabs)(label-on[0].value);

	if(error>thresholdError)
{
	train(in,hn,on,inputFeatures,label);
}

}

float generateRandomWeights()
{
	float result = 0;
	result = (float)(rand() % 1000);
	result = result - 500;
	result = result / 1000;
	return result;
}
void printNetwork(InputNode in[], HiddenNode hn[], OutputNode on[], float weights[], float biases[])
{
	int index = 0;
	//salvo i pesi tra nodi input e hidden
	//weights contiene pesi salvati in questo ordine: tutti i pesi tra nodo 1 e hidden, tutti pesi tra nodo 2 e hid e così via
	for (int i = 0; i < nOfFeatures; i++)
	{
		for (int h = 0; h < nOfHiddenNodes; h++)
		{
			weights[index] = in[i].weights[h];
			index++;
		}
	}
	//salvo pesi tra hidden e out
	for (int h = 0; h < nOfHiddenNodes; h++)
	{
		for (int o = 0; o < nOfOutputNodes; o++)
		{
			weights[index] = hn[h].weights[o];
			index++;
		}
	}
	index = 0;
	for (int h = 0; h < nOfHiddenNodes; h++)
	{
		biases[index] = hn[h].bias;
		index++;
	}
	for (int o = 0; o < nOfOutputNodes; o++)
	{
		biases[index] = on[o].bias;
		index++;
	}

	index = 0;

	//in[0].weights[0]= 0.050364453;
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

			printf("%.9f", weights[index]);
			//printf(";\n");
			printf("\n");
			index++;
		}
	}
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

			printf("%.9f", weights[index]);
			//printf(";\n");
			printf("\n");
			index++;
		}
	}
	index = 0;
	//printf("#Bias nodi hidden:\n");
	for (int h = 0; h < nOfHiddenNodes; h++)
	{

		//printf("hn[");
		//printf("%i", h);
		//printf("].bias");
		//printf("= ");

		printf("%.9f", biases[index]);
		//printf(";\n");
		printf("\n");
		index++;
	}
	//printf("#Bias nodi(o) output:\n");
	for (int o = 0; o < nOfOutputNodes; o++)
	{
		//printf("on[");
		//printf("%i", o);
		//printf("].bias");
		//printf("= ");

		printf("%.9f", biases[index]);
		//printf(";\n");
		printf("\n");
		index++;
	}
}
