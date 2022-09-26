const int NUM_I = 2;
const int NUM_H = 2;
const int NUM_O = 2;

double I[NUM_I] = {0.05, 0.10};
double T[NUM_O] = {0.01, 0.99}; //
double H[NUM_H];
double O[NUM_O];

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

void dnn_test() {
	
	srand(time(NULL));
	
	initialize_weight_He((double *)WH, NUM_I, NUM_H); //
	print("WH =", (double *)WH, NUM_I, NUM_H);
	
	initialize_weight_Le((double *)WO, NUM_H, NUM_O); //
	print("WO =", (double *)WO, NUM_H, NUM_O);
	
	for(int epoch=1;epoch<1000001;epoch++) {
	
		forward_Y(I, (double *)WH, BH, H, NUM_I, NUM_H);
		relu_Y(H, NUM_H); //
	
		forward_Y(H, (double *)WO, BO, O, NUM_H, NUM_O);
		sigmoid_Y(O, NUM_O); //
			
		double E = calculate_MSE(O, T, NUM_O); //
		
		if(epoch==1) { //
			printf("\nepoch = %d\n", epoch);
			printf("Error = %.4f\n", E);
			print("O =", O, NUM_O);
		}
		
		if(E < 0.0001) { //
			printf("\nepoch = %d\n", epoch);
			printf("Error = %.4f\n", E);
			print("O =", O, NUM_O);
			break;
		}
	
		backward_Yb(Ob, O, T, NUM_O);
		sigmoid_Xb(Ob, O, NUM_O); //
		
		backward_Xb(Hb, (double *)WO, Ob, NUM_H, NUM_O);
		relu_Xb(Hb, H, NUM_H); //
		
		backward_Wb(H, (double *)WOb, Ob, NUM_H, NUM_O);		
		backward_Bb(BOb, Ob, NUM_O);
		
		backward_Wb(I, (double *)WHb, Hb, NUM_I, NUM_H);		
		backward_Bb(BHb, Hb, NUM_H);
		
		double lr = 0.01;
		
		learning_W((double *)WO, lr, (double *)WOb, NUM_H, NUM_O);	
		learning_B(BO, lr, BOb, NUM_O);
		
		learning_W((double *)WH, lr, (double *)WHb, NUM_I, NUM_H);	
		learning_B(BH, lr, BHb, NUM_H);
		
	}
	
}

void setup() {

	Serial.begin(115200);
	delay(1000);

	dnn_test();

}

void loop() {

}