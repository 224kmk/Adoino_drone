const int NUM_I = 2;
const int NUM_H = 2;
const int NUM_O = 2;

double I[NUM_I] = {0.05, 0.10};
double T[NUM_O] = {0.01, 0.99};
double H[NUM_H];
double O[NUM_O];

double WH[NUM_I][NUM_H] = {
	{0.15, 0.25},
	{0.20, 0.30}
};
double BH[NUM_H] = {0.35, 0.35};
double WO[NUM_H][NUM_O] = {
	{0.40, 0.50},
	{0.45, 0.55}
};
double BO[NUM_O] = {0.60, 0.60};

double Ob[NUM_O];
double Hb[NUM_H];
double WOb[NUM_H][NUM_O];
double BOb[NUM_O];
double WHb[NUM_I][NUM_H];
double BHb[NUM_H];

void dnn_test() {
	
	for(int epoch=0;epoch<1000;epoch++) {

		printf("\nepoch = %d\n", epoch);
	
		forward_Y(I, (double *)WH, BH, H, NUM_I, NUM_H);
		print("H =", H, NUM_H);
	
		forward_Y(H, (double *)WO, BO, O, NUM_H, NUM_O);
		print("O =", O, NUM_O);
			
		double E = calculate_MSE(O, T, NUM_O);
		printf("E = %.7f\n", E);
		
		if(E < 0.0000001)
			break;
	
		backward_Yb(Ob, O, T, NUM_O);
		print("Ob =", Ob, NUM_O);
		
		backward_Xb(Hb, (double *)WO, Ob, NUM_H, NUM_O);
		print("Hb =", Hb, NUM_H);
		
		backward_Wb(H, (double *)WOb, Ob, NUM_H, NUM_O);
		print("WOb =", (double *)WOb, NUM_H, NUM_O);
		
		backward_Bb(BOb, Ob, NUM_O);
		print("BOb =", BOb, NUM_O);
		
		backward_Wb(I, (double *)WHb, Hb, NUM_I, NUM_H);
		print("WHb =", (double *)WHb, NUM_I, NUM_H);
		
		backward_Bb(BHb, Hb, NUM_H);
		print("BHb =", BHb, NUM_H);
		
		double lr = 0.01;
		
		learning_W((double *)WO, lr, (double *)WOb, NUM_H, NUM_O);
		print("WO =", (double *)WO, NUM_H, NUM_O);
		
		learning_B(BO, lr, BOb, NUM_O);
		print("BO =", BO, NUM_O);
		
		learning_W((double *)WH, lr, (double *)WHb, NUM_I, NUM_H);
		print("WH =", (double *)WH, NUM_I, NUM_H);
		
		learning_B(BH, lr, BHb, NUM_H);
		print("BH =", BH, NUM_H);
	}
	
}

void setup() {

	Serial.begin(115200);
	delay(1000);

	dnn_test();

}

void loop() {

}