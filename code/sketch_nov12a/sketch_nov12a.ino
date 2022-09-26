const int MOTOR_A =23;
const int MOTOR_B =19;
const int MOTOR_C =18;
const int MOTOR_D =26;
const int CHANNEL_A =0;
const int CHANNEL_B =1;
const int CHANNEL_C =2;
const int CHANNEL_D =3;
const int MOTOR_FREQ =5000;
const int MOTOR_RESOLUTION =10;

const int melody[] = { 262, 294, 330, 349, 393, 440, 494, 523, };

void setup() {
  ledcAttachPin(MOTOR_A, CHANNEL_A);
  ledcAttachPin(MOTOR_B, CHANNEL_B);
  ledcAttachPin(MOTOR_C, CHANNEL_C);
  ledcAttachPin(MOTOR_D, CHANNEL_D);
  
  ledcSetup(CHANNEL_A, MOTOR_FREQ, MOTOR_RESOLUTION);
  ledcSetup(CHANNEL_B, MOTOR_FREQ, MOTOR_RESOLUTION);
  ledcSetup(CHANNEL_C, MOTOR_FREQ, MOTOR_RESOLUTION);
  ledcSetup(CHANNEL_D, MOTOR_FREQ, MOTOR_RESOLUTION);
  
  ledcWrite(CHANNEL_A,0);
  ledcWrite(CHANNEL_B,0);
  ledcWrite(CHANNEL_C,0);
  ledcWrite(CHANNEL_D,0);

  delay(3000);  
}

unsigned int howMany =3;

void loop() {
  if(howMany >0){
     howMany --;
     
     ledcWrite(CHANNEL_A,100); delay(1000);
     ledcWrite(CHANNEL_B,100); delay(1000);
     ledcWrite(CHANNEL_C,100); delay(1000);
     ledcWrite(CHANNEL_D,100); delay(1000);

     ledcWrite(CHANNEL_A,0);
     ledcWrite(CHANNEL_B,0);
     ledcWrite(CHANNEL_C,0);
     ledcWrite(CHANNEL_D,0);
     delay(4000);

  }
 
}
