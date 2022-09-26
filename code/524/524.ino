const int NUM_PATTERN = 10;
const int NUM_I = 7;
const int NUM_H = 16; //
const int NUM_M = 16; //
const int NUM_O = 4;

double I[NUM_PATTERN][NUM_I] = {
	{ 1, 1, 1, 1, 1, 1, 0 },  // 0
	{ 0, 1, 1, 0, 0, 0, 0 },  // 1
	{ 1, 1, 0, 1, 1, 0, 1 },  // 2
	{ 1, 1, 1, 1, 0, 0, 1 },  // 3
	{ 0, 1, 1, 0, 0, 1, 1 },  // 4
	{ 1, 0, 1, 1, 0, 1, 1 },  // 5
	{ 0, 0, 1, 1, 1, 1, 1 },  // 6
	{ 1, 1, 1, 0, 0, 0, 0 },  // 7 
	{ 1, 1, 1, 1, 1, 1, 1 },  // 8
	{ 1, 1, 1, 0, 0, 1, 1 }   // 9
};
double T[NUM_PATTERN][NUM_O] = {
	{ 0, 0, 0, 0 },  
	{ 0, 0, 0, 1 }, 
	{ 0, 0, 1, 0 }, 
	{ 0, 0, 1, 1 }, 
	{ 0, 1, 0, 0 }, 
	{ 0, 1, 0, 1 }, 
	{ 0, 1, 1, 0 }, 
	{ 0, 1, 1, 1 }, 
	{ 1, 0, 0, 0 }, 
	{ 1, 0, 0, 1 } 
};
double H[NUM_H];
double M[NUM_M]; //
double O[NUM_PATTERN][NUM_O];

double WH[NUM_I][NUM_H];
double BH[NUM_H];
double WM[NUM_H][NUM_M]; //
double BM[NUM_M]; //
double WO[NUM_M][NUM_O]; //
double BO[NUM_O];

double Ob[NUM_O];
double Mb[NUM_M]; //
double Hb[NUM_H];
double WOb[NUM_M][NUM_O]; //
double BOb[NUM_O];
double WMb[NUM_H][NUM_M]; //
double BMb[NUM_M]; //
double WHb[NUM_I][NUM_H];
double BHb[NUM_H];

int shuffled_pattern[NUM_PATTERN]; //

void dnn_test() {
	
	srand(time(NULL));
	
	initialize_weight_He((double *)WH, NUM_I, NUM_H);
	
	initialize_weight_He((double *)WM, NUM_H, NUM_M); //
		
	initialize_weight_Le((double *)WO, NUM_M, NUM_O); //

	for(int pc=0;pc<NUM_PATTERN;pc++) {
		shuffled_pattern[pc] = pc;
	}
	
	long begin = millis(); //
	
	for(int epoch=1;epoch<10001;epoch++) {
		
		int tmp_a = 0;
		int tmp_b = 0;
		for(int pc=0;pc<NUM_PATTERN;pc++) {
			tmp_a = rand()%NUM_PATTERN;
			tmp_b = shuffled_pattern[pc];
			shuffled_pattern[pc] = shuffled_pattern[tmp_a];
			shuffled_pattern[tmp_a] = tmp_b;
		}
		
		double sumError = 0;
		
		static long t_prev = millis();
		
		for(int rc=0;rc<NUM_PATTERN;rc++) {
			
			int pc = shuffled_pattern[rc];
	
			forward_Y(I[pc], (double *)WH, BH, H, NUM_I, NUM_H);
			relu_Y(H, NUM_H);
	
			forward_Y(H, (double *)WM, BM, M, NUM_H, NUM_M); //
			relu_Y(M, NUM_M); //
			
			forward_Y(M, (double *)WO, BO, O[pc], NUM_M, NUM_O); //
			sigmoid_Y(O[pc], NUM_O);
				
			double E = calculate_MSE(O[pc], T[pc], NUM_O);
			
			sumError += E;
		
			backward_Yb(Ob, O[pc], T[pc], NUM_O);
			sigmoid_Xb(Ob, O[pc], NUM_O);
				
			backward_Xb(Mb, (double *)WO, Ob, NUM_M, NUM_O); //
			relu_Xb(Mb, M, NUM_M); //
				
			backward_Xb(Hb, (double *)WM, Mb, NUM_H, NUM_M); //
			relu_Xb(Hb, H, NUM_H);
			
			backward_Wb(M, (double *)WOb, Ob, NUM_M, NUM_O); //
			backward_Bb(BOb, Ob, NUM_O);
			
			backward_Wb(H, (double *)WMb, Mb, NUM_H, NUM_M); //
			backward_Bb(BMb, Mb, NUM_M); //
			
			backward_Wb(I[pc], (double *)WHb, Hb, NUM_I, NUM_H);
			backward_Bb(BHb, Hb, NUM_H);
			
			double lr = 0.01;
			
			learning_W((double *)WO, lr, (double *)WOb, NUM_M, NUM_O); //
			learning_B(BO, lr, BOb, NUM_O);
			
			learning_W((double *)WM, lr, (double *)WMb, NUM_H, NUM_M); //
			learning_B(BM, lr, BMb, NUM_M); //
			
			learning_W((double *)WH, lr, (double *)WHb, NUM_I, NUM_H);
			learning_B(BH, lr, BHb, NUM_H);
			
		}
		if(epoch%100==0) {
			long t_now = millis(); //
			long time_taken = t_now - t_prev; //
			t_prev = t_now; //
			printf("epoch : %5d, sum error : %f ", epoch, sumError); //
			printf(", %.3f sec\n", time_taken/1000.0); //
			
			if(sumError<0.0001) break;
		}
	
	}
	printf("\n");

	for(int pc=0;pc<NUM_PATTERN;pc++) {
		printf("target %d : ", pc);
		for(int on=0;on<NUM_O;on++) {
			printf("%.0f ", T[pc][on]);
		}
		printf("pattern %d : ", pc);
		for(int on=0;on<NUM_O;on++) {
			printf("%.2f ", O[pc][on]);
		}
		printf("\n");
	}
	
	long end = millis();
	long time_taken = end - begin;
	printf("\nTotal time taken (in seconds) %.3f\n", time_taken/1000.0);	
}

void setup() {

	Serial.begin(115200);
	delay(1000);

	dnn_test();

}

void loop() {

}