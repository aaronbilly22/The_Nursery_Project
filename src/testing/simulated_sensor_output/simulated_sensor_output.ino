#define PIN 7

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PIN, HIGH);
  delay(1000);
  digitalWrite(PIN, LOW);
  delay(5000);
}
