#define PIN_LED 11
int timeout = 5;
void setup() {
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  for(int i=0;i<255;i++) {
    analogWrite(PIN_LED, i);
    delay(timeout);  
  }
  for(int i=255;i>=0;i--) {
    analogWrite(PIN_LED, i);
    delay(timeout);  
  }
  
}
