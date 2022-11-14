#define A 2
#define B 3
#define C 4
#define D 5
#define NUMBER_OF_STEPS_PER_REV 512
#define signalPin 10
int signalPin_state = 0;

void setup() {
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
  pinMode(signalPin_state,INPUT);
  Serial.begin(9600);
}


void write(int a,int b,int c,int d){
  digitalWrite(A,a);
  digitalWrite(B,b);
  digitalWrite(C,c);
  digitalWrite(D,d);
}

void onestep(){
  write(1,0,0,0);
  delay(1);
  write(1,1,0,0);
  delay(1);
  write(0,1,0,0);
  delay(1);
  write(0,1,1,0);
  delay(1);
  write(0,0,1,0);
  delay(1);
  write(0,0,1,1);
  delay(1);
  write(0,0,0,1);
  delay(1);
  write(1,0,0,1);
  delay(1);
}
void loop() {
  signalPin_state = digitalRead(signalPin);

  Serial.println(signalPin_state);
  
  if(signalPin_state==HIGH){
    onestep();
  }

  
}
