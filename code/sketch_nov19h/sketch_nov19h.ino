void backward_Wb(double *X, double *Wb, double *Yb, int M, int N) {
  for(int m=0;m<M;m++) 
    for(int n=0;n<N;n++)   
      Wb[m*N+n] = X[m]*Yb[n]; 
}

void print(char * s, double *W, int M, int N) {
  printf("%s [\n", s);
  for(int m=0;m<M;m++) {
    printf("[", s);
    for(int n=0;n<N-1;n++) 
      printf("%.3f ", W[m*N+n]);    
    printf("%.3f]\n", W[m*N+N-1]);
  }
  printf("]\n");
}

const int M = 2;
const int N = 2;

double X[N] = {2, 3};
double Yb[M] = {-8, 60};
double Wb[M][N] = {0,};

void dnn_test() {
  
  backward_Wb(X, (double *)Wb, Yb, M, N);
  print("Wb =", (double *)Wb, M, N);
  
}

void setup() {

  Serial.begin(115200);
  delay(1000);

  dnn_test();
  
}

void loop() {

}
