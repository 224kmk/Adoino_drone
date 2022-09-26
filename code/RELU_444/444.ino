// 출력층에 softmax 함수 적용하기
double i1 = 0.05, i2 = 0.10;
double t1 =    0, t2 =    1;

double w1 = 0.15, w3 = 0.25;
double w2 = 0.20, w4 = 0.30;
double b1 = 0.35, b2 = 0.35;

double w5 = 0.40, w7 = 0.50;
double w6 = 0.45, w8 = 0.55;
double b3 = 0.60, b4 = 0.60;

void dnn_test() {
	
	for(int epoch=0;epoch<2000000;epoch++) {

		if(epoch%1000==999) printf("epoch = %d\n", epoch);
		
		double h1 = i1*w1 + i2*w2 + 1*b1;
		double h2 = i1*w3 + i2*w4 + 1*b2;
		h1 = 1/(1+exp(-h1)); // ➊
		h2 = 1/(1+exp(-h2)); // ➊
		
		double o1 = h1*w5 + h2*w6 + 1*b3;
		double o2 = h1*w7 + h2*w8 + 1*b4;
		double o1m = o1 - max(o1, o2); // ➐
		double o2m = o2 - max(o1, o2); // ➐
		o1 = exp(o1m)/(exp(o1m)+exp(o2m)); // ➐
		o2 = exp(o2m)/(exp(o1m)+exp(o2m)); // ➐
		
		if(epoch%1000==999) printf(" o1,  o2  = %6.3f, %6.3f\n", o1, o2);
		
		double E = -t1*log(o1) + -t2*log(o2); // ➑
		if(epoch%1000==999) printf(" E  = %.7f\n", E);
		if (E < 0.0001) {
			printf("epoch = %d\n", epoch);
			printf(" o1,  o2  = %6.3f, %6.3f\n", o1, o2);
			printf(" E  = %.7f\n", E);
			break;
		}
		
		double o1b = o1 - t1, o2b = o2 - t2; // ➒
   
		// nothing for softmax + cross entropy error
		
		double h1b = o1b*w5+o2b*w7, h2b = o1b*w6+o2b*w8;
		h1b = h1b*h1*(1-h1), h2b = h2b*h2*(1-h2); // ➋
		
		double w1b = i1*h1b, w3b = i1*h2b;
		double w2b = i2*h1b, w4b = i2*h2b;
		double b1b = 1*h1b, b2b = 1*h2b;
		double w5b = h1*o1b, w7b = h1*o2b;
		double w6b = h2*o1b, w8b = h2*o2b;
		double b3b = 1*o1b, b4b = 1*o2b;
		
		double lr = 0.01;
		w1 = w1 - lr*w1b, w3 = w3 - lr*w3b;
		w2 = w2 - lr*w2b, w4 = w4 - lr*w4b;
		b1 = b1 - lr*b1b, b2 = b2 - lr*b2b;
		w5 = w5 - lr*w5b, w7 = w7 - lr*w7b;
		w6 = w6 - lr*w6b, w8 = w8 - lr*w8b;
		b3 = b3 - lr*b3b, b4 = b4 - lr*b4b;
		
	}
	
}

void setup() {

	Serial.begin(115200);
	delay(1000);

	dnn_test();
  
}

void loop() {

}
