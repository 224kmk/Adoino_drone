double x1 =2, x2 = 3;
double t1 = 27, t2 = -30;
double w1 = 3, w3 = 5;
double w2 = 4, w4 = 6;
double b1 = 1, b2 = 2;

void dnn_test() {
  
  for(int epoch=0;epoch<2000;epoch++) {

    printf("epoch = %d\n", epoch);
    
    double y1 = x1*w1 + x2*w2 + 1*b1; // ➊
    double y2 = x1*w3 + x2*w4 + 1*b2; // ➊
    printf(" y1,  y2  = %6.3f, %6.3f\n", y1, y2);
    
    double E = (y1-t1)*(y1-t1)/2 + (y2-t2)*(y2-t2)/2;
    printf(" E  = %.7f\n", E);
    if(E < 0.0000001)
      break;

    double y1b = y1 - t1, y2b = y2 - t2;
    double x1b = y1b*w1+y2b*w3, x2b = y1b*w2+y2b*w4; // ➋
    double w1b = x1*y1b, w3b = x1*y2b; // ➌
    double w2b = x2*y1b, w4b = x2*y2b; // ➌
    double b1b = 1*y1b, b2b = 1*y2b; // ➍
    printf(" x1b, x2b = %6.3f, %6.3f\n", x1b, x2b);
    printf(" w1b, w3b = %6.3f, %6.3f\n", w1b, w3b);
    printf(" w2b, w4b = %6.3f, %6.3f\n", w2b, w4b);
    printf(" b1b, b2b = %6.3f, %6.3f\n", b1b, b2b);

    double lr = 0.01; 
    w1 = w1 - lr*w1b, w3 = w3 -lr*w3b; // ➎
    w2 = w2 - lr*w2b, w4 = w4 -lr*w4b; // ➎
    b1 = b1 - lr*b1b, b2 = b2 - lr*b2b; // ➏
    printf(" w1,  w3  = %6.3f, %6.3f\n", w1, w3);
    printf(" w2,  w4  = %6.3f, %6.3f\n", w2, w4);
    printf(" b1,  b2  = %6.3f, %6.3f\n", b1, b2);
    
  }
  
}

void setup() {

  Serial.begin(115200);
  delay(1000);

  dnn_test();
  
}

void loop() {

}
