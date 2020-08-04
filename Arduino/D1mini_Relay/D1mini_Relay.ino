const int relayPin = D1;

void setup() {
  pinMode(relayPin, OUTPUT);
}

void loop() {
  digitalWrite(relayPin, HIGH); // turn on relay with voltage HIGH
  delay(2000);              // pause
  digitalWrite(relayPin, LOW);  // turn off relay with voltage LOW
  delay(2000);              // pause
}
