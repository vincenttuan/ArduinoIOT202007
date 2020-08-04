void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // D1 mini 預設 LED
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);   
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(2000);    
}
