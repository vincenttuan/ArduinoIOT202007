const int relayPin = D1;
const int reedPin = D2;

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(reedPin, INPUT_PULLUP);
}

void loop() {
  int reed = digitalRead(reedPin);
  Serial.println(reed);
  if(reed)
    digitalWrite(relayPin, HIGH); // turn on relay with voltage HIGH
  else
    digitalWrite(relayPin, LOW);  // turn off relay with voltage LOW
  
  delay(500);
}
