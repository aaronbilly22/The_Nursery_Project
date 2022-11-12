#define A 4
#define B 3
#define C 2
#define D 1
#define NUMBER_OF_STEPS_PER_REV 512

void setup() {
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
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
  int i=0;
  while(i<NUMBER_OF_STEPS_PER_REV){
    onestep();
    i++;
  }
}
