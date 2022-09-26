double xs[] = {-1, 0, 1, 2,  3,  4};
double ys[] = {-2, 1, 4, 7, 10, 13};
double w = 10;
double b = 10;

void dnn_test() {
  
  for(int n=0;n<6;n++) {

    double y = xs[n]*w + 1*b;
    printf("x  = %6.3f, y  = %6.3f\n", xs[n], y);

    double t = ys[n];
    double E = (y-t)*(y-t)/2;
    printf("E  = %.7f\n", E);

    double yb = y - t;
    double wb = yb*xs[n];
    double bb = yb*1;
    printf("wb = %6.3f, bb = %6.3f\n", wb, bb);

    double lr = 0.01;
    w = w - lr*wb;
    b = b - lr*bb;
    printf("w  = %6.3f, b  = %6.3f\n", w, b); 

    for(int n=0;n<25;n++) printf("=");
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
