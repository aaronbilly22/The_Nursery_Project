const int TRIG_PIN = 6; // Arduino pin connected to Ultrasonic Sensor's TRIG pin
const int ECHO_PIN = 2; // Arduino pin connected to Ultrasonic Sensor's ECHO pin
const int TRIG2_PIN = 8; // Arduino pin connected to Ultrasonic Sensor's TRIG pin
const int ECHO2_PIN = 3; // Arduino pin connected to Ultrasonic Sensor's ECHO pin
const int LED_PIN  = 4; // Arduino pin connected to LED's pin
const int LED2_PIN  = 9; // Arduino pin connected to LED's pin
const int relayPin = 10;
const int stopPin = 11;

const int DISTANCE_MIN = 12; // centimeters
const int DISTANCE_MAX = 16; // centimeters

// variables will change:
float duration_us, distance_cm, duration2_us, distance2_cm, data, SerialData, UltraSensor, UltraSensor2, distance1, distance2;

void setup() {
  Serial.begin (9600);       // initialize serial port
  pinMode(TRIG_PIN, OUTPUT); // set arduino pin to output modez
  pinMode(ECHO_PIN, INPUT);  // set arduino pin to input mod=e
  pinMode(TRIG2_PIN, OUTPUT); // set arduino pin to output mode
  pinMode(ECHO2_PIN, INPUT);  // set arduino pin to input mode
  pinMode(LED_PIN, OUTPUT);  // set arduino pin to output mode
  pinMode(LED2_PIN, OUTPUT);  // set arduino pin to output mode

  pinMode(relayPin, OUTPUT); // signal pin to relay
  pinMode(stopPin, INPUT); // signal from pot dropper to stop/start conveyor
  
}
void loop() {
  
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // measure duration of pulse from ECHO pin
  
  duration_us = pulseIn(ECHO_PIN, HIGH);

  delayMicroseconds(50);
  digitalWrite(TRIG2_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG2_PIN, LOW);  
  
  duration2_us = pulseIn(ECHO2_PIN, HIGH);
  
  // calculate the distance
  distance_cm = 0.017 * duration_us;
  distance2_cm = 0.017 * duration2_us; 

  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  
  Serial.print("distance 2: ");
  Serial.print(distance2_cm);
  Serial.println(" cm");


  if(DISTANCE_MAX > distance_cm && distance_cm > DISTANCE_MIN || DISTANCE_MAX > distance2_cm && distance2_cm > DISTANCE_MIN )
    
    digitalWrite(LED_PIN, HIGH);// turn on LED
    
  else
    digitalWrite(LED_PIN, LOW);// turn off LED 
 
  if(digitalRead(stopPin)==HIGH){
    digitalWrite(relayPin, LOW);
  }
  else{
    digitalWrite(relayPin, HIGH);
  }
} 
