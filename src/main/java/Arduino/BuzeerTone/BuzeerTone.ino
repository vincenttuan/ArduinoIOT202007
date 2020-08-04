const int PIN_BUZEER = 3;
int timeout = 500;
int frequences[] = {1046, 1175, 1318, 1397, 1568, 1760, 1976};
void setup() {
  pinMode(PIN_BUZEER, HIGH);

  for(int i = 0; i < 7 ; i++) {
    tone(PIN_BUZEER, frequences[i], timeout);
    delay(timeout);    
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
