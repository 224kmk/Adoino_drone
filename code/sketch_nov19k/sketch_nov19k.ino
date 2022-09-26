void forward_Y(double *X, double *W, double *B, double *Y, int M, int N) {
  for(int n=0;n<N;n++) Y[n] = 0;  
  for(int m=0;m<M;m++) 
    for(int n=0;n<N;n++)   
      Y[n] += X[m]*W[m*N+n];  
  for(int n=0;n<N;n++) Y[n] += B[n];  
}

void print(char * s, double *Y, int N) {
  printf("%s [", s);
  for(int n=0;n<N-1;n++) printf("%.3f ", Y[n]);
  printf("%.3f]\n", Y[N-1]);  
}

const int M = 2;
const int N = 2;

double X[M] = {2, 3};
double W[M][N] = {
  {3, 5},
  {4, 6}
};
double B[N] = {1, 2};
double Y[N] = {0, 0};
double T[N] = {27, -30};

void dnn_test() {
  
  forward_Y(X, (double *)W, B, Y, M, N);
  print("Y =", Y, N);
  
}

void setup() {

  Serial.begin(115200);
  delay(1000);

  dnn_test();
  
}

void loop() {

}
