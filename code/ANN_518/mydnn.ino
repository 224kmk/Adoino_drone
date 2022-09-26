void forward_Y(double *X, double *W, double *B, double *Y, int M, int N) {	
	for(int n=0;n<N;n++) Y[n] = 0;	
	for(int m=0;m<M;m++) 
		for(int n=0;n<N;n++)   
			Y[n] += X[m]*W[m*N+n];	
	for(int n=0;n<N;n++) Y[n] += B[n];  
}

double calculate_MSE(double *Y, double *T, int N) {	
	double E = 0;
	for(int n=0;n<N;n++) E += (Y[n]-T[n])*(Y[n]-T[n])/2;	
	return E;
}

void backward_Yb(double *Yb, double *Y, double *T, int N) {
	for(int n=0;n<N;n++) Yb[n] = Y[n] - T[n];
}

void backward_Xb(double *Xb, double *W, double *Yb, int M, int N) {
	for(int m=0;m<M;m++) Xb[m] = 0;	
	for(int m=0;m<M;m++) 
		for(int n=0;n<N;n++)   
			Xb[m] += Yb[n]*W[m*N+n];	
}

void backward_Wb(double *X, double *Wb, double *Yb, int M, int N) {
	for(int m=0;m<M;m++) 
		for(int n=0;n<N;n++)   
			Wb[m*N+n] = X[m]*Yb[n];	
}

void backward_Bb(double *Bb, double *Yb, int N) {
	for(int n=0;n<N;n++) Bb[n] = Yb[n];
}

void learning_W(double *W, double lr, double *Wb, int M, int N) {
	for(int m=0;m<M;m++) 
		for(int n=0;n<N;n++)   
			W[m*N+n] -= lr * Wb[m*N+n];
}

void learning_B(double *B, double lr, double *Bb, int N) {
	for(int n=0;n<N;n++) B[n] -= lr * Bb[n];	
}

void sigmoid_Y(double *Y, int N) {
	for(int n=0;n<N;n++) Y[n] = 1/(1 + exp(-Y[n]));
}

void sigmoid_Xb(double *Xb, double *X, int M) {
	for(int m=0;m<M;m++) Xb[m] = Xb[m]*X[m]*(1-X[m]);
}	

void tanh_Y(double *Y, int N) {
	for(int n=0;n<N;n++) Y[n] = tanh(Y[n]);
}

void tanh_Xb(double *Xb, double *X, int M) {
	for(int m=0;m<M;m++) Xb[m] = Xb[m]*(1+X[m])*(1-X[m]);
}

void relu_Y(double *Y, int N) {
	for(int n=0;n<N;n++) Y[n] = (Y[n]>0?1:0)*Y[n];
}

void relu_Xb(double *Xb, double *X, int M) {
	for(int m=0;m<M;m++) Xb[m] = Xb[m]*(X[m]>0?1:0)*1;
}

void print(char * s, double *Y, int N) {
	printf("%s [", s);
	for(int n=0;n<N-1;n++) printf("%.3f ", Y[n]);
	printf("%.3f]\n", Y[N-1]);	
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