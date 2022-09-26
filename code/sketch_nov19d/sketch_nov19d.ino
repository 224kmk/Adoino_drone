double x = 2;
double t = 10;
double w = 3;
double b = 1;

void dnn_test(){
  for (int epoch=0; epoch<200; epoch++){
    printf("epoch = %d\n", epoch);

    double y = x*w + 1*b;
    printf(" y = %6.3f\n", y);

    double E = (y - t)*(y - t) / 2;
    printf(" E = %.7f\n", E);
    if ( E < 0.0000001)
      break;

    double yb = y - t;
    double xb = yb*w;
    double wb = yb*x;
    double bb = yb*1;
    printf(" xb = %6.3f, wb = %6.3f, bb = %6.3f\n", xb, wb, bb);

    double lr=0.005;
    w = w - lr*wb;
    b = b - lr*bb;
    printf(" x = %6.3f, w = %6.3f, b = %6.3f\n", x, w, b);

  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  dnn_test();

}

void loop() {
  // put your main code here, to run repeatedly:

}
