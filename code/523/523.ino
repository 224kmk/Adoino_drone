const int NUM_PATTERN = 10;
const int NUM_I = 7;
const int NUM_H = 8;
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
double O[NUM_PATTERN][NUM_O];

double WH[NUM_I][NUM_H];
double BH[NUM_H];
double WO[NUM_H][NUM_O];
double BO[NUM_O];

double Ob[NUM_O];
double Hb[NUM_H];
double WOb[NUM_H][NUM_O];
double BOb[NUM_O];
double WHb[NUM_I][NUM_H];
double BHb[NUM_H];

int shuffled_pattern[NUM_PATTERN]; //

void dnn_test() {
	
	srand(time(NULL));
	
	initialize_weight_He((double *)WH, NUM_I, NUM_H);
		
	initialize_weight_Le((double *)WO, NUM_H, NUM_O);

	for(int pc=0;pc<NUM_PATTERN;pc++) { //
		shuffled_pattern[pc] = pc; //
	}  //
	
	for(int epoch=1;epoch<10001;epoch++) {
		
		int tmp_a = 0;  //
		int tmp_b = 0;  //
		for(int pc=0;pc<NUM_PATTERN;pc++) {  //
			tmp_a = rand()%NUM_PATTERN;  //
			tmp_b = shuffled_pattern[pc];  //
			shuffled_pattern[pc] = shuffled_pattern[tmp_a];  //
			shuffled_pattern[tmp_a] = tmp_b;  //
		}  //
		
		double sumError = 0;
		
		for(int rc=0;rc<NUM_PATTERN;rc++) {  //
			
			int pc = shuffled_pattern[rc];  //
	
			forward_Y(I[pc], (double *)WH, BH, H, NUM_I, NUM_H);
			relu_Y(H, NUM_H);
		
			forward_Y(H, (double *)WO, BO, O[pc], NUM_H, NUM_O);
			sigmoid_Y(O[pc], NUM_O);
				
			double E = calculate_MSE(O[pc], T[pc], NUM_O);
			
			sumError += E; //
		
			backward_Yb(Ob, O[pc], T[pc], NUM_O);
			sigmoid_Xb(Ob, O[pc], NUM_O);
				
			backward_Xb(Hb, (double *)WO, Ob, NUM_H, NUM_O);
			relu_Xb(Hb, H, NUM_H);
			
			backward_Wb(H, (double *)WOb, Ob, NUM_H, NUM_O);
			backward_Bb(BOb, Ob, NUM_O);
			
			backward_Wb(I[pc], (double *)WHb, Hb, NUM_I, NUM_H);
			backward_Bb(BHb, Hb, NUM_H);
			
			double lr = 0.01;
			
			learning_W((double *)WO, lr, (double *)WOb, NUM_H, NUM_O);
			learning_B(BO, lr, BOb, NUM_O);
			
			learning_W((double *)WH, lr, (double *)WHb, NUM_I, NUM_H);
			learning_B(BH, lr, BHb, NUM_H);
			
		}
		if(epoch%100==0) {		
			printf("epoch : %5d, sum error : %f\n", epoch, sumError);
			for(int i=0;i<NUM_I;i++) {
				for(int j=0;j<NUM_H;j++) {
					printf("%7.3f ", WH[i][j]);
				}     
				printf("\n");
			}    
			
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
	
}

void setup() {

	Serial.begin(115200);
	delay(1000);

	dnn_test();

}

void loop() {

}