double x1 =2, x2 = 3;
double t = 27;
double w1 = 3;
double w2 = 4;
double b = 1;

void dnn_test() {
  
  for(int epoch=0;epoch<2000;epoch++) {

    printf("epoch = %d\n", epoch);
    
    double y = x1*w1 + x2*w2 + 1*b; // ➊
    printf(" y  = %6.3f\n", y);
    
    double E = (y-t)*(y-t)/2;
    printf(" E  = %.7f\n", E);
    if(E < 0.0000001)
      break;

    double yb = y - t;
    double x1b = yb*w1, x2b = yb*w2; // ➋
    double w1b = yb*x1; // ➌
    double w2b = yb*x2; // ➌
    double bb = yb*1; // ➍
    printf(" x1b, x2b = %6.3f, %6.3f\n", x1b, x2b);
    printf(" w1b, w2b, bb = %6.3f, %6.3f, %6.3f\n", w1b, w2b, bb);

    double lr = 0.01; 
    w1 = w1 - lr*w1b; // ➎ 
    w2 = w2 - lr*w2b; // ➎ 
    b = b - lr*bb; // ➏
    printf(" w1,  w2,  b  = %6.3f, %6.3f, %6.3f\n", w1, w2, b);
    
  }
  
}

void setup() {

  Serial.begin(115200);
  delay(1000);

  dnn_test();
  
}

void loop() {

}
