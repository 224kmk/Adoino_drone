const int NUM_X = 2;
const int NUM_Y = 2;

double X[NUM_X] = {2, 3};
double T[NUM_Y] = {27, -30};
double Y[NUM_Y];

double W[NUM_X][NUM_Y] = {
  {3, 5},
  {4, 6}
};
double B[NUM_Y] = {1, 2};

double Yb[NUM_Y];
double Xb[NUM_X];
double Wb[NUM_X][NUM_Y];
double Bb[NUM_Y];

void dnn_test() { 
  
  forward_Y(X, (double *)W, B, Y, NUM_X, NUM_Y);
  print("Y =", Y, NUM_Y);
    
  double E = calculate_MSE(Y, T, NUM_Y);
  printf("E = %.7f\n", E);
  
  backward_Yb(Yb, Y, T, NUM_Y);
  print("Yb =", Yb, NUM_Y);
  
  backward_Xb(Xb, (double *)W, Yb, NUM_X, NUM_Y);
  print("Xb =", Xb, NUM_X);
  
  backward_Wb(X, (double *)Wb, Yb, NUM_X, NUM_Y);
  print("Wb =", (double *)Wb, NUM_X, NUM_Y);
  
  backward_Bb(Bb, Yb, NUM_Y);
  print("Bb =", Bb, NUM_Y);
  
  double lr = 0.01;
  learning_W((double *)W, lr, (double *)Wb, NUM_X, NUM_Y);
  print("W =", (double *)W, NUM_X, NUM_Y);
  
  learning_B(B, lr, Bb, NUM_Y);
  print("B =", B, NUM_Y);
  
}

void setup() {

  Serial.begin(115200);
  delay(1000);

  dnn_test();

}

void loop() {

}
