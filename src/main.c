#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "main.h"


int main(void)
{
	HAL_Init();
	MX_USART2_UART_Init();
	I2C1_init();
	BSP_LED_Init(LED2);
//verifico l'effettiva presenza del sensore sul bus i2c e nel caso, inizializzo
	if (LSM6DSL_Who_Am_I() == LSM6DSL_WHO_AM_I_VAL)
	{
		LSM6DSL_present = ENABLE;
		char *msg = "\n\rLSM6DSL found on the I2C bus! \r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*) msg, strlen(msg), 0xFFFF);
		LSM6DSL_Config();
	}
	else
	{
		char *msg = "\n\rNOT FOUND \r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*) msg, strlen(msg), 0xFFFF);
		LSM6DSL_present = DISABLE;
	}
	//caratteri utilizzati frequentemente nell'output (debug)
	char buffer[100];
	char *newline = "\n\r";
	char *tab = "\t";
	char *virgola = ",";
	char *openGraffa = "{";
	char *closeGraffa = "}";

//	char *sep="#################";
//	char *media="media: ";

	//liste contenenti i neuroni divisi per livello
	InputNode inputNodes[nOfFeatures];
	HiddenNode hiddenNodes[nOfHiddenNodes];
	OutputNode outputNodes[nOfOutputNodes];

	//valori che decidono il funzionamento del dispositivo
	//tipo di funzionamento
	int mode = WORK_MODE_LOAD_NETWORK_FROM_FUNCTION;//WORK_MODE_RANDOM_SETUP  WORK_MODE_TRAIN_FROM_DATA_IN_PROGRAM WORK_MODE_LOAD_NETWORK_FROM_FUNCTION
	//abilitazione del crosstrain
	int ct = CROSSTRAIN_DISABLED;
	//training che assicura l'utilizzo di ogni elemento del training set o training random
	int tr_mode = TRAINING_MODE_FULL;
	//mostrare i dati letti dal sensore ad ogni ciclo
	int show_sens_data = NOT_SHOW_SENS_DATA;

	//generazione di un seed per il generatore di numeri casuali tramite funzione apposita
	int seed = Rand_value_acc();
	srand(seed);

	//training set
	float trainingSetFeatures[nOfSamples][nOfFeatures] =
	{
			{0.021725,      0.031302,       1.028945,       -1.113525,      -3.755325,      -14.811301,     0.040323,       0.075775,       0.056705,       1.135966,       3.787384,       15.840349,      -1.000000,      0.260084,       -1.000000,      },
			{0.021322,      0.033197,       1.032046,       1.372700,       -2.085125,      18.608095,      0.026683,       0.039839,       0.033599,       1.351642,       2.118697,       17.576080,      1.000000,       -1.000000,      -1.000000,      },
			{0.017691,      0.032962,       1.030418,       1.002400,       -2.020725,      15.943550,      0.020326,       0.032759,       0.038411,       0.984918,       2.053948,       14.913181,      1.000000,       0.685874,       -1.000000,      },
			{0.008926,      0.019439,       1.034458,       -0.425600,      -2.385775,      7.916300,       0.019576,       0.034892,       0.037047,       0.434966,       2.405467,       6.881943,       0.089293,       -0.566571,      -1.000000,      },
			{0.019313,      0.010069,       1.028721,       -0.526225,      -3.298575,      -17.014898,     0.032603,       0.027594,       0.016303,       0.546511,       3.308758,       18.043629,      -1.000000,      0.039119,       -0.194879,      },
			{0.003765,      0.025283,       1.025271,       -0.003500,      -2.548000,      -5.303375,      0.024230,       0.031880,       0.033399,       0.025296,       2.573481,       6.328734,       -1.000000,      0.763298,       -1.000000,      },
			{0.004092,      0.015110,       1.034320,       0.134925,       -2.551675,      5.946326,       0.034534,       0.032306,       0.023197,       0.135314,       2.566988,       4.912061,       -0.390024,      0.521044,       1.000000,       },
			{0.014397,      0.023203,       1.032365,       -0.205975,      -3.009650,      -4.269650,      0.021975,       0.033525,       0.039113,       0.221465,       3.033039,       5.302160,       -1.000000,      -0.302425,      -1.000000,      },
			{0.015278,      0.020100,       1.030149,       -0.273175,      -2.912000,      -13.206373,     0.030160,       0.028272,       0.022635,       0.290025,       2.932236,       14.236540,      -1.000000,      1.000000,       -1.000000,      },
			{-0.003558,     0.037790,       1.033655,       -0.205975,      -3.291750,      -13.654202,     0.023031,       0.029634,       0.024130,       0.203723,       3.329671,       14.687878,      0.356312,       -1.000000,      1.000000,       },
			{0.003304,      0.055817,       1.030568,       1.048775,       -1.944075,      19.521425,      0.024911,       0.037541,       0.022935,       1.045768,       2.000245,       18.490871,      1.000000,       0.013443,       1.000000,       },
			{0.011940,      0.021603,       1.032404,       1.063475,       -2.255225,      13.514374,      0.031034,       0.032198,       0.040649,       1.051993,       2.277055,       12.482036,      -0.505897,      -1.000000,      1.000000,       },
			{0.008714,      0.029562,       1.033404,       -0.139125,      -1.881600,      14.251124,      0.023878,       0.031392,       0.036209,       0.149756,       1.911420,       13.217771,      1.000000,       -0.461327,      -1.000000,      },
			{0.024964,      0.021172,       1.025836,       0.021350,       -2.371600,      11.266151,      0.028062,       0.031918,       0.039101,       0.028293,       2.392985,       10.240390,      -1.000000,      0.021169,       -1.000000,      },
			{0.030204,      0.030954,       1.029273,       0.749000,       -2.147425,      8.043700,       0.027266,       0.025213,       0.026640,       0.719314,       2.178525,       7.014478,       0.308678,       0.683120,       -1.000000,      },
			{0.005921,      0.014822,       1.032236,       0.396375,       -2.309300,      18.108124,      0.026869,       0.029090,       0.020606,       0.391378,       2.324304,       17.075901,      -1.000000,      0.102508,       -0.681946,      },
			{0.006461,      0.017905,       1.033492,       -0.466550,      -3.711575,      -22.421873,     0.026396,       0.028536,       0.026271,       0.473747,       3.729589,       23.455379,      -1.000000,      -0.140334,      1.000000,       },
			{0.006063,      0.013884,       1.030136,       0.499800,       -2.988650,      -5.634122,      0.027585,       0.034616,       0.037812,       0.494506,       3.002733,       6.664366,       -0.469521,      -0.773704,      -1.000000,      },
			{0.008489,      0.021487,       1.034012,       0.811300,       -3.273026,      -9.663674,      0.026521,       0.040902,       0.033873,       0.803249,       3.294766,       10.697740,      1.000000,       1.000000,       1.000000,       },
			{0.053646,      -0.001266,      1.027898,       1.763825,       -2.550100,      19.034399,      0.033840,       0.029039,       0.022731,       1.710514,       2.548999,       18.006516,      1.000000,       0.784308,       -1.000000,      },
			{0.028763,      0.000389,       1.026823,       -0.026250,      -2.982874,      -4.167276,      0.027632,       0.031501,       0.026002,       0.061563,       2.983430,       5.194164,       0.700046,       0.550659,       1.000000,       },
			{0.016342,      0.006620,       1.025932,       0.865550,       -2.861425,      7.340024,       0.028173,       0.031140,       0.034110,       0.849675,       2.868214,       6.314185,       1.000000,       0.271175,       -1.000000,      },
			{0.013177,      0.010185,       1.032176,       -0.500325,      -3.416175,      -1.676674,      0.035112,       0.042195,       0.035133,       0.514701,       3.426620,       2.709078,       -1.000000,      -0.337130,      -1.000000,      },
			{0.010704,      -0.007491,      1.029544,       0.609175,       -2.930550,      11.319348,      0.041544,       0.047169,       0.046473,       0.599911,       2.923440,       10.289909,      -0.640926,      -1.000000,      1.000000,       },
			{0.030238,      0.000049,       1.023267,       1.073275,       -2.933000,      7.211576,       0.032654,       0.047324,       0.061974,       1.043548,       2.933430,       6.188620,       1.000000,       1.000000,       -1.000000,      },
			{0.014999,      -0.013560,      1.029665,       -0.123200,      -3.649274,      -19.504976,     0.032950,       0.037142,       0.040589,       0.142072,       3.635904,       20.534681,      -1.000000,      -1.000000,      1.000000,       },
			{0.012765,      -0.008751,      1.030456,       -1.286950,      -3.173275,      -14.879897,     0.025165,       0.046439,       0.055382,       1.299959,       3.164865,       15.910449,      -1.000000,      1.000000,       -1.000000,      },
			{0.020902,      -0.012271,      1.027484,       0.872550,       -2.867900,      10.763900,      0.027330,       0.032997,       0.042969,       0.852086,       2.855820,       9.736510,       -0.035325,      -1.000000,      -1.000000,      },
			{0.018817,      -0.005079,      1.037279,       1.045450,       -1.984675,      8.576925,       0.035918,       0.038614,       0.036185,       1.027261,       1.979973,       7.539733,       -1.000000,      -1.000000,      1.000000,       },
			{0.007000,      0.028594,       1.029514,       1.385825,       -2.418324,      6.016850,       0.038255,       0.045562,       0.050013,       1.379355,       2.447343,       4.987586,       -1.000000,      -1.000000,      -1.000000,      },
			{0.005017,      0.007336,       1.024844,       0.816550,       -2.520350,      10.875550,      0.032297,       0.039237,       0.045016,       0.812176,       2.527990,       9.850810,       1.000000,       -1.000000,      -1.000000,      },
			{0.014430,      -0.010787,      1.031287,       0.718900,       -2.970275,      12.739998,      0.037896,       0.028228,       0.024603,       0.705488,       2.959622,       11.708737,      -1.000000,      1.000000,       1.000000,       },
			{0.006738,      0.002307,       1.031538,       -0.486500,      -2.626225,      -3.272326,      0.027010,       0.027764,       0.034285,       0.493977,       2.628679,       4.303999,       0.979960,       0.410584,       -1.000000,      },
			{0.018749,      -0.000035,      1.031117,       -0.607600,      -2.776375,      -15.600373,     0.029224,       0.027425,       0.030569,       0.627030,       2.776474,       16.631517,      -1.000000,      0.397869,       1.000000,       },
			{0.016346,      0.005396,       1.026393,       0.736400,       -2.442650,      19.910101,      0.027082,       0.030803,       0.027280,       0.720563,       2.448240,       18.883728,      1.000000,       0.357930,       -1.000000,      },
			{0.010898,      -0.008552,      1.039368,       0.915250,       -2.570050,      12.932673,      0.030681,       0.028788,       0.030599,       0.904872,       2.561660,       11.893343,      0.149985,       -1.000000,      1.000000,       },
			{0.027832,      0.001900,       1.027584,       -1.114575,      -2.942275,      -15.523203,     0.026896,       0.035266,       0.032714,       1.142723,       2.944386,       16.550819,      1.000000,       -1.000000,      1.000000,       },
			{0.011318,      -0.006598,      1.025717,       -0.187775,      -2.875600,      -12.618901,     0.025909,       0.039624,       0.042932,       0.200772,       2.869276,       13.644687,      1.000000,       1.000000,       -1.000000,      },
			{0.012288,      -0.015928,      1.028171,       0.498050,       -2.425325,      24.889027,      0.029603,       0.030049,       0.036021,       0.486663,       2.409584,       23.860882,      1.000000,       0.008229,       -1.000000,      },
			{0.011384,      0.009301,       1.030138,       0.048125,       -2.602075,      -3.459749,      0.029222,       0.032829,       0.038749,       0.046945,       2.611582,       4.490054,       1.000000,       1.000000,       -0.314905,      },
			{0.012666,      0.011117,       1.033967,       0.624400,       -3.471825,      -7.221200,      0.037511,       0.036214,       0.030086,       0.612883,       3.483130,       8.255221,       -0.567043,      0.345762,       1.000000,       },
			{0.017975,      0.010393,       1.034694,       -0.509250,      -2.875250,      -4.389175,      0.033654,       0.034457,       0.033870,       0.528298,       2.885849,       5.423975,       -1.000000,      0.012546,       -1.000000,      },
			{0.014614,      0.016537,       1.030295,       -0.051800,      -3.122525,      -5.481001,      0.025591,       0.025692,       0.028602,       0.071174,       3.139167,       6.511358,       -1.000000,      -1.000000,      1.000000,       },
			{0.040007,      0.018692,       1.031167,       0.550900,       -2.121525,      4.959679,       0.037880,       0.035698,       0.027719,       0.512295,       2.140514,       3.928609,       -1.000000,      -1.000000,      1.000000,       },
			{0.011001,      -0.020052,      1.033409,       0.736575,       -2.477300,      20.385574,      0.029290,       0.033054,       0.036563,       0.726165,       2.457470,       19.352198,      0.218454,       0.274164,       -1.000000,      },
			{0.011192,      -0.023232,      1.028757,       1.453375,       -3.050600,      10.153324,      0.025883,       0.038991,       0.038978,       1.442415,       3.027619,       9.124651,       1.000000,       0.974177,       1.000000,       },
			{0.012952,      -0.043125,      1.029005,       -0.398300,      -2.575300,      -0.998724,      0.042177,       0.041925,       0.035359,       0.413409,       2.532522,       2.028038,       -1.000000,      1.000000,       -1.000000,      },
			{0.016321,      -0.035642,      1.027235,       -0.935375,      -2.498825,      -12.026532,     0.033571,       0.033227,       0.025229,       0.952288,       2.463407,       13.053792,      0.547361,       1.000000,       -1.000000,      },
			{0.007932,      -0.027193,      1.029602,       -1.435175,      -2.762025,      -11.477549,     0.029596,       0.031415,       0.025712,       1.443411,       2.735013,       12.507178,      -1.000000,      1.000000,       1.000000,       },
			{0.009255,      -0.022820,      1.036716,       0.287350,       -2.878225,      13.587700,      0.028874,       0.032805,       0.041227,       0.279590,       2.855593,       12.551050,      0.629501,       0.113542,       1.000000,       },

			{-0.070892,     0.030600,       1.015728,       -0.467775,      -1.473850,      -12.533501,     0.169800,       0.082487,       0.157351,       0.431681,       1.506710,       13.550142,      -1.000000,      1.000000,       -1.000000,      },
			{-0.039734,     0.023456,       1.030240,       -6.470274,      13.517176,      28.494902,      0.177771,       0.112166,       0.118330,       6.432997,       13.494186,      27.464914,      -1.000000,      1.000000,       1.000000,       },
			{-0.022288,     0.105047,       1.009489,       2.791250,       -3.523451,      1.502550,       0.157854,       0.118209,       0.108205,       2.817963,       3.630422,       0.504794,       -1.000000,      1.000000,       1.000000,       },
			{-0.014780,     0.001757,       1.008447,       2.866499,       -0.777350,      14.321302,      0.176340,       0.088658,       0.139596,       2.886671,       0.784135,       13.313589,      -1.000000,      1.000000,       1.000000,       },
			{-0.010921,     -0.077798,      1.003122,       -1.420300,      -1.398075,      7.936953,       0.190659,       0.156279,       0.150966,       1.422216,       1.329494,       6.935474,       -1.000000,      1.000000,       -1.000000,      },
			{-0.032096,     -0.011452,      1.001663,       0.960225,       -2.836050,      3.347751,       0.214026,       0.164690,       0.146988,       1.015139,       2.829395,       2.350689,       1.000000,       1.000000,       -1.000000,      },
			{0.027222,      -0.113471,      0.994001,       -0.131075,      -3.680251,      9.463299,       0.203274,       0.125220,       0.145894,       0.257640,       3.568977,       8.470554,       -1.000000,      1.000000,       -1.000000,      },
			{-0.006557,     -0.119933,      1.003740,       2.595600,       -4.607750,      -9.425675,      0.192825,       0.151016,       0.110863,       2.609292,       4.490357,       10.430005,      -1.000000,      1.000000,       1.000000,       },
			{-0.010702,     0.044797,       1.000074,       -0.157500,      -4.290300,      -12.104223,     0.170567,       0.151064,       0.105466,       0.225039,       4.337729,       13.104722,      -1.000000,      1.000000,       1.000000,       },
			{-0.143407,     0.020625,       1.002201,       0.908075,       -0.586075,      -14.083824,     0.119584,       0.166188,       0.110194,       1.058260,       0.629050,       15.086428,      1.000000,       -1.000000,      -1.000000,      },
			{0.008586,      -0.100019,      1.000516,       5.337325,       -0.548275,      -11.663225,     0.185992,       0.113124,       0.100656,       5.331984,       0.462310,       12.664141,      -1.000000,      1.000000,       -1.000000,      },
			{-0.125813,     -0.118445,      0.994134,       0.623875,       -4.163600,      10.991925,      0.184425,       0.136338,       0.077645,       0.772038,       4.047452,       9.998092,       -1.000000,      -1.000000,      -1.000000,      },
			{-0.017031,     -0.043536,      0.987940,       5.546625,       -1.959300,      1.915025,       0.265248,       0.090862,       0.119130,       5.569976,       1.917917,       0.934708,       1.000000,       -1.000000,      1.000000,       },
			{-0.025250,     -0.027969,      0.984685,       1.069775,       -5.268725,      -12.589325,     0.198675,       0.206127,       0.127966,       1.112903,       5.244808,       13.574613,      -1.000000,      -1.000000,      -1.000000,      },
			{0.006730,      -0.112695,      1.016619,       0.447300,       -5.656701,      8.341375,       0.255223,       0.093653,       0.109968,       0.509157,       5.544796,       7.325583,       1.000000,       1.000000,       1.000000,       },
			{0.158307,      -0.066351,      0.994257,       -2.419025,      -7.323925,      -7.212625,      0.194393,       0.092301,       0.112857,       2.584653,       7.258161,       8.207658,       -1.000000,      1.000000,       1.000000,       },
			{-0.016126,     0.003897,       1.012296,       2.855125,       -3.252550,      4.666900,       0.157431,       0.091294,       0.091459,       2.875563,       3.257726,       3.655748,       1.000000,       1.000000,       -1.000000,      },
			{-0.049897,     -0.045096,      0.984035,       -0.158550,      -2.740500,      20.139870,      0.251139,       0.180226,       0.127370,       0.273636,       2.701423,       19.156258,      1.000000,       1.000000,       1.000000,       },
			{-0.001806,     -0.036153,      0.995082,       -3.154551,      -3.132850,      1.701525,       0.284509,       0.105716,       0.141674,       3.165556,       3.098500,       0.720509,       1.000000,       1.000000,       -1.000000,      },
			{-0.004634,     -0.048352,      0.988734,       1.360099,       -3.797324,      -3.514175,      0.222317,       0.207322,       0.107851,       1.382722,       3.754700,       4.504200,       1.000000,       1.000000,       0.910333,       },
			{0.115461,      -0.051920,      0.995577,       -0.396900,      -2.034025,      -0.568050,      0.218181,       0.130809,       0.120923,       0.556881,       1.986417,       1.568296,       -1.000000,      1.000000,       1.000000,       },
			{-0.042599,     -0.013357,      0.999814,       5.398926,       -7.625100,      19.492725,      0.269985,       0.127145,       0.127088,       5.448218,       7.612806,       18.493347,      1.000000,       1.000000,       1.000000,       },
			{0.013763,      0.057479,       0.974407,       2.408700,       -1.410676,      22.894726,      0.273731,       0.228344,       0.146784,       2.410529,       1.485806,       21.920809,      1.000000,       -1.000000,      1.000000,       },
			{-0.043018,     0.033053,       0.974385,       -2.452450,      -5.108249,      -3.637725,      0.285093,       0.161200,       0.106898,       2.426239,       5.143829,       4.613348,       1.000000,       1.000000,       -1.000000,      },
			{-0.006246,     0.078847,       0.989651,       2.632175,       -1.095500,      4.424700,       0.216044,       0.201683,       0.118780,       2.647251,       1.191540,       3.437103,       -1.000000,      -1.000000,      1.000000,       },
			{0.004698,      0.080973,       0.997319,       -1.201025,      -3.962874,      3.698624,       0.259517,       0.122379,       0.140329,       1.233336,       4.045698,       2.704947,       -1.000000,      1.000000,       1.000000,       },
			{0.041861,      -0.101411,      0.990359,       -2.197825,      -2.259600,      -12.745423,     0.269350,       0.120374,       0.126257,       2.255824,       2.161544,       13.736362,      -1.000000,      -1.000000,      1.000000,       },
			{-0.089558,     -0.105840,      0.984524,       -1.881075,      -1.915375,      1.682800,       0.281113,       0.127219,       0.153754,       1.813439,       1.814002,       0.715003,       1.000000,       1.000000,       -1.000000,      },
			{0.075030,      -0.035439,      1.004349,       -0.146125,      -1.382675,      2.787399,       0.187614,       0.119880,       0.124915,       0.290015,       1.352559,       1.787420,       -1.000000,      -1.000000,      1.000000,       },
			{-0.007591,     -0.162691,      0.992115,       2.895899,       -0.895651,      -31.768274,     0.226853,       0.134666,       0.136731,       2.912339,       0.745228,       32.760670,      -1.000000,      1.000000,       -1.000000,      },
			{0.085157,      -0.081040,      0.998314,       -1.177575,      -1.165676,      -6.119575,      0.215016,       0.142443,       0.126769,       1.280908,       1.093949,       7.119018,       -1.000000,      -1.000000,      1.000000,       },
			{-0.049111,     -0.322662,      0.981618,       0.638050,       -7.208776,      7.016100,       0.158481,       0.107669,       0.111296,       0.705200,       6.886956,       6.035508,       1.000000,       -1.000000,      -1.000000,      },
			{-0.003521,     -0.196017,      0.979915,       0.152075,       0.293476,       8.110201,       0.184713,       0.277952,       0.166640,       0.241514,       0.562904,       7.132233,       1.000000,       1.000000,       1.000000,       },
			{-0.185669,     -0.195377,      0.986191,       -0.648025,      -5.881751,      1.266476,       0.150320,       0.161201,       0.125610,       0.486178,       5.688658,       0.307144,       1.000000,       1.000000,       -1.000000,      },
			{0.067188,      -0.184386,      0.985426,       3.648925,       -0.440300,      -11.310426,     0.215975,       0.134225,       0.108386,       3.588242,       0.288978,       12.296329,      -1.000000,      1.000000,       1.000000,       },
			{-0.096207,     -0.304573,      0.969992,       4.957225,       -2.507050,      -3.468850,      0.203364,       0.150017,       0.160884,       5.057522,       2.207580,       4.441756,       1.000000,       1.000000,       1.000000,       },
			{-0.076291,     -0.142311,      1.007787,       1.096550,       -2.949275,      -4.266674,      0.200913,       0.090679,       0.105700,       1.189926,       2.808429,       5.275520,       -1.000000,      1.000000,       1.000000,       },
			{-0.100812,     0.027698,       0.982346,       1.276800,       -0.874475,      18.193001,      0.201994,       0.258474,       0.106158,       1.392342,       0.938469,       17.210981,      1.000000,       1.000000,       -1.000000,      },
			{0.018400,      -0.146879,      1.023109,       -0.697375,      -3.840725,      4.150649,       0.116711,       0.115311,       0.159743,       0.725228,       3.695645,       3.131617,       1.000000,       1.000000,       -1.000000,      },
			{-0.030717,     -0.192704,      1.017565,       0.465850,       -7.004725,      3.795575,       0.111798,       0.180118,       0.162603,       0.508997,       6.814402,       2.782764,       1.000000,       1.000000,       -1.000000,      },
			{-0.030294,     -0.147104,      1.011971,       -4.148376,      -4.115125,      -13.924228,     0.210584,       0.136806,       0.134995,       4.123463,       3.970379,       14.936809,      1.000000,       1.000000,       1.000000,       },
			{-0.061742,     -0.137660,      0.967189,       1.791650,       2.137799,       -15.520752,     0.228701,       0.235015,       0.107353,       1.867449,       2.287563,       16.488291,      1.000000,       -1.000000,      1.000000,       },
			{-0.028415,     -0.005846,      0.994094,       1.068025,       -0.055825,      3.606225,       0.162204,       0.250345,       0.093759,       1.108373,       0.255285,       2.613814,       -1.000000,      -1.000000,      1.000000,       },
			{0.104292,      -0.115283,      0.996791,       -2.757300,      0.325850,       -3.165050,      0.198679,       0.126007,       0.089679,       2.868481,       0.458776,       4.162807,       -1.000000,      -1.000000,      1.000000,       },
			{-0.176530,     0.042445,       0.999373,       4.442899,       -4.437125,      -23.339397,     0.147187,       0.153472,       0.079574,       4.621774,       4.482198,       24.338903,      -1.000000,      -1.000000,      1.000000,       },
			{0.038558,      -0.163794,      0.991149,       -2.839551,      3.616200,       -23.903599,     0.209207,       0.138077,       0.086289,       2.885702,       3.782514,       24.894899,      -1.000000,      1.000000,       1.000000,       },
			{-0.179684,     0.012335,       0.976039,       0.704025,       -4.488050,      -2.862125,      0.229205,       0.200909,       0.102800,       0.912949,       4.504869,       3.839540,       1.000000,       1.000000,       -1.000000,      },
			{0.116545,      -0.142989,      0.997251,       -5.531924,      -1.104425,      -16.431623,     0.228091,       0.152278,       0.105440,       5.653073,       0.973421,       17.429195,      -1.000000,      -1.000000,      1.000000,       },
			{0.073593,      -0.009133,      1.024385,       -0.308175,      0.053550,       -16.725628,     0.139869,       0.121507,       0.116396,       0.406583,       0.136723,       17.750393,      -1.000000,      -1.000000,      -1.000000,      },
			{-0.030099,     -0.026256,      0.990094,       0.522725,       -7.131950,      -3.076150,      0.264366,       0.146813,       0.124320,       0.612784,       7.107211,       4.068144,       1.000000,       1.000000,       -1.000000,      }
	};
	//etichette associate ai vettori di training
	int trainingLabels[nOfSamples] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
									   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	//normalizzazione del training set
	float max_values[nOfFeatures] = { 0 };

	for (int i = 0; i < nOfFeatures; i++)
	{
		for (int sample = 0; sample < nOfSamples; sample++)
		{
			float temp_val = fabs(trainingSetFeatures[sample][i]);
			if (temp_val > max_values[i])
			{
				max_values[i] = temp_val;
			}
		}
	}
	for (int i = 0; i < nOfFeatures; i++)
	{
		for (int sample = 0; sample < nOfSamples; sample++)
		{
			trainingSetFeatures[sample][i] = trainingSetFeatures[sample][i]	/ max_values[i];
		}
	}
	//serve per l'eventuale crosstrain
	int indexNoTrain[sampleToAvoid * 2] = { 0 };

	//selezione della modalità di funzionamento in base alla variabile "mode"
	switch (mode)
	{
	//inizializzazione della rete tramite valori random
	case WORK_MODE_RANDOM_SETUP:
		randomSetupNodes(inputNodes, hiddenNodes, outputNodes);
		break;
	//caricamento dei valori della rete da valori cablati nella funzione "loadTrainedNetwork"
	//(sono) valori ricavati da un training, il contenuto della funzione è scritto in console da
	//"printNetwork"
	case WORK_MODE_LOAD_NETWORK_FROM_FUNCTION:
		loadTrainedNetwork(inputNodes, hiddenNodes, outputNodes);
		break;
	//caricamento da file (non funzionante al momento)
	/*
	case WORK_MODE_LOAD_NETWORK_FROM_FILE:
		loadTrainedNetworkFromFile(inputNodes, hiddenNodes, outputNodes);
		break;
		*/
	//addestramento della rete utilizzando il training set cablato nel programma
	case WORK_MODE_TRAIN_FROM_DATA_IN_PROGRAM:

		randomSetupNodes(inputNodes, hiddenNodes, outputNodes);

		//se il crosstrain è abilitato:
		//suddivido il training set in training e test con percentuali 70 e 30 => 70 vettori di training (35 per ogni classe) e 30 di test (15 per ogni classe)
		//generazione dei 15+15 indici random
		if (ct == CROSSTRAIN_ENABLED)
		{
			int temp = 0;
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
					train(inputNodes, hiddenNodes, outputNodes, trainingSetFeatures[i], trainingLabels[i]);
				}
				train_index = true;
				if (indexNoTrain[c2] == i + nOfSamples / 2)
				{
					c2++;
					train_index = false;
				}
				if (train_index)
				{
					train(inputNodes, hiddenNodes, outputNodes, trainingSetFeatures[i + nOfSamples / 2], trainingLabels[i + nOfSamples / 2]);
				}
				train_index = true;
			}
			//verifico l'etichetta dei 15+15 vettori esclusi (test set)
			int ct_labels[sampleToAvoid*2]={0};
			int tmp_ind;
			for (int i = 0;i<sampleToAvoid*2;i++)
			{
				tmp_ind=indexNoTrain[i];
				ct_labels[i]=calculateSampleLabel(inputNodes,hiddenNodes,outputNodes,trainingSetFeatures[tmp_ind]);
			}
			//stampa i valori
			for (int i = 0;i<sampleToAvoid*2;i++)
			{
				snprintf(buffer, sizeof buffer, "%i", ct_labels[i]);
				HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer), 0xFFFF);
				HAL_UART_Transmit(&huart2, (uint8_t*) newline, strlen(newline), 0xFFFF);
			}
		}
		//no crosstrain
		else
		{
			//se training mode random scelgo casualmente "randomTrainingModeCycles" volte
			//coppie di vettori (una per classe) e addestro la rete su di esse
			if (tr_mode == TRAINING_MODE_RANDOM)
			{
				for (int cycles = 0; cycles < randomTrainingModeCycles; cycles++)
				{
					int index = rand() % 50;
					train(inputNodes, hiddenNodes, outputNodes, trainingSetFeatures[index], trainingLabels[index]);
					index = (rand() % 50) + 50;
					train(inputNodes, hiddenNodes, outputNodes, trainingSetFeatures[index], trainingLabels[index]);
				}
			}
			//se invece voglio avere certezza di utilizzare tutti i vettori li considero uno alla volta (ognuno una volta solo)
			else if (tr_mode == TRAINING_MODE_FULL)
			{
				for (int i = 0; i < nOfSamples / 2; i++)
				{
					train(inputNodes, hiddenNodes, outputNodes,	trainingSetFeatures[i], trainingLabels[i]);
					train(inputNodes, hiddenNodes, outputNodes,	trainingSetFeatures[i + nOfSamples / 2],trainingLabels[i + nOfSamples / 2]);
				}
			}
		}
		break;
	}//fine switch
	//contenitori temporanei per accogliere i dati sensoriali
	float acc[3] = { 0 };
	float gyro[3] = { 0 };
	int cycleNum = 0;

	//contengono i campioni che vengono composti e vengono classificati
	float sampleToClassify_accelerationX[vectorLength] = { 0 };
	float sampleToClassify_accelerationY[vectorLength] = { 0 };
	float sampleToClassify_accelerationZ[vectorLength] = { 0 };

	float sampleToClassify_gyroX[vectorLength] = { 0 };
	float sampleToClassify_gyroY[vectorLength] = { 0 };
	float sampleToClassify_gyroZ[vectorLength] = { 0 };

	//contenitore per le features del vettore che viene classificato
	float sampleFeatures[nOfFeatures] = { 0 };

	//int cycleNumber=0;

	/*
	//test var

	float test[8]={1,7,3,9,10,22,0,6};

	float test_mean = calculateMean(test);
	snprintf(buffer, sizeof buffer, "%f", test_mean);
	HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*) newline, strlen(newline), 0xFFFF);

	float var_test=calculateVar(test, test_mean);
	snprintf(buffer, sizeof buffer, "%f", var_test);
	HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*) newline, strlen(newline), 0xFFFF);

	float std_dev=sqrt(var_test);
	snprintf(buffer, sizeof buffer, "%f", std_dev);
	HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*) newline, strlen(newline), 0xFFFF);
*/
	//etichetta del campione classificato
	int c_label;
	float out_value;
	char *class="";

	//printNetwork(inputNodes,hiddenNodes,outputNodes);
int cycleNumber=0;

	for (;;)
	{
		//lettura valori
		LSM6DSL_ReadAcceleration(acc);
		LSM6DSL_ReadGyro(gyro);
//stampa valori ad ogni giro

/*
		snprintf(buffer, sizeof buffer, "%i", cycleNum);
		HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer),0xFFFF);
*/
		if(show_sens_data == SHOW_SENS_DATA)
		{
		for (int i = 0; i < 3; i++)
		{
			snprintf(buffer, sizeof buffer, "%f", acc[i]);
			HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*) tab, strlen(tab), 0xFFFF);
		}
		for (int i = 0; i < 3; i++)
		{
			snprintf(buffer, sizeof buffer, "%f", gyro[i]);
			HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*) tab, strlen(tab), 0xFFFF);
		}
		HAL_UART_Transmit(&huart2, (uint8_t*) newline, strlen(newline), 0xFFFF);
		}
		//se il vettore da classificare non è ancora pieno aggiungo il valore appena letto
		if (cycleNum < vectorLength)
		{
			sampleToClassify_accelerationX[cycleNum] = acc[0];
			sampleToClassify_accelerationY[cycleNum] = acc[1];
			sampleToClassify_accelerationZ[cycleNum] = acc[2];
			/*
			 for(int i = 0; i<3;i++)
			 {
			 snprintf(buffer, sizeof buffer, "%f", acc[i]);
			 HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
			 HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
			 }
			 */
			sampleToClassify_gyroX[cycleNum] = gyro[0];
			sampleToClassify_gyroY[cycleNum] = gyro[1];
			sampleToClassify_gyroZ[cycleNum] = gyro[2];
			/*
			 for(int i = 0; i<3;i++)
			 {
			 snprintf(buffer, sizeof buffer, "%f", gyro[i]);
			 HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
			 HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
			 }
			 HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
			 */
			cycleNum++;
		}
		//altrimenti vengono estratte le features
		else
		{
			cycleNumber++;
			cycleNum = 0;
/*
			for(int i = 0; i<vectorLength;i++)
			{
				snprintf(buffer, sizeof buffer, "%f", sampleToClassify_gyroX[i]);
				HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer), 0xFFFF);
				HAL_UART_Transmit(&huart2, (uint8_t*) newline, strlen(newline), 0xFFFF);
			}
*/
			sampleFeatures[0] = calculateMean(sampleToClassify_accelerationX);
			sampleFeatures[1] = calculateMean(sampleToClassify_accelerationY);
			sampleFeatures[2] = calculateMean(sampleToClassify_accelerationZ);
			sampleFeatures[3] = calculateMean(sampleToClassify_gyroX);
			sampleFeatures[4] = calculateMean(sampleToClassify_gyroY);
			sampleFeatures[5] = calculateMean(sampleToClassify_gyroZ);
			sampleFeatures[6] = sqrt(calculateVar(sampleToClassify_accelerationX,sampleFeatures[0]));
			sampleFeatures[7] = sqrt(calculateVar(sampleToClassify_accelerationY,sampleFeatures[1]));
			sampleFeatures[8] = sqrt(calculateVar(sampleToClassify_accelerationZ,sampleFeatures[2]));
			sampleFeatures[9] = sqrt(calculateVar(sampleToClassify_accelerationX,sampleFeatures[3]));
			sampleFeatures[10] = sqrt(calculateVar(sampleToClassify_accelerationY,sampleFeatures[4]));
			sampleFeatures[11] = sqrt(calculateVar(sampleToClassify_accelerationZ,sampleFeatures[5]));
			sampleFeatures[12] = calculateCorr(sampleToClassify_accelerationX,sampleToClassify_gyroX, sampleFeatures[0],sampleFeatures[3], sampleFeatures[6], sampleFeatures[9]);
			sampleFeatures[13] = calculateCorr(sampleToClassify_accelerationY,sampleToClassify_gyroY, sampleFeatures[1],sampleFeatures[4], sampleFeatures[7], sampleFeatures[10]);
			sampleFeatures[14] = calculateCorr(sampleToClassify_accelerationZ,sampleToClassify_gyroZ, sampleFeatures[2],sampleFeatures[5], sampleFeatures[8], sampleFeatures[11]);


			 HAL_UART_Transmit(&huart2, (uint8_t*)openGraffa, strlen(openGraffa), 0xFFFF);
			 for(int ri = 0; ri<nOfFeatures; ri++)
			 {
				 snprintf(buffer, sizeof buffer, "%f", sampleFeatures[ri]);
				 HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
				 HAL_UART_Transmit(&huart2, (uint8_t*)virgola, strlen(virgola), 0xFFFF);
				 HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
			 }
			 HAL_UART_Transmit(&huart2, (uint8_t*)closeGraffa, strlen(closeGraffa), 0xFFFF);
			 HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
//vengono normalizzate le features estratte
			 for (int i=0;i<nOfFeatures;i++)
			 {
				 sampleFeatures[i]=sampleFeatures[i]/max_values[i];
			 }
			 //si calcola l'output della rete fornendo il vettore come input
			 c_label = calculateSampleLabel(inputNodes,hiddenNodes,outputNodes,sampleFeatures);
			 snprintf(buffer, sizeof buffer, "%i", c_label);
			 HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
			 HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);

			 out_value = calculateOutput(inputNodes,hiddenNodes,outputNodes,sampleFeatures);
			 snprintf(buffer, sizeof buffer, "%f", out_value);
			 HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);

			 //snprintf(buffer, sizeof buffer, "%i", cycleNumber);
			 //HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
			 //per etichetta 0 il campione è considerato come alterato e viene acceso il LED come
			 //feedback visivo per l'utente, in caso contrario esso viene spento
			/*
			 if (c_label == 0)
			{
				class=" alterato\t\t";
				BSP_LED_On(LED2);
			}
			else
			{
				class=" normale\t\t";
				BSP_LED_Off(LED2);
			}
			*/
			HAL_UART_Transmit(&huart2, (uint8_t*) newline, strlen(newline),	0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*)class, strlen(class), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*) newline, strlen(newline),	0xFFFF);

			if(cycleNumber==20)
			{
				char *msg2="fine numero50";
				HAL_UART_Transmit(&huart2, (uint8_t*) newline, strlen(newline),0xFFFF);
				HAL_UART_Transmit(&huart2, (uint8_t*) msg2, strlen(msg2),0xFFFF);
			}

		}
		//HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
		HAL_Delay(sampleTime);
	}
}
//non potendo utilizzare la data e ora (time(NULL)) come seed per la funzione srand di inizializzazione
//del generatore di numeri casuali si utilizza un valore preso dal sensore (nel caso accelerazione su asse z)
int Rand_value_acc()
{
	int val = 0;
	float temp = 0.0;
	float acc_val[3] = { 0 };
	LSM6DSL_ReadAcceleration(acc_val);
	temp = acc_val[2] * 10000000;
	val = (int) temp;
	return val;
}
