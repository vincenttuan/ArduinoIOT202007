#define PIN_BUTTON 7
int preValue = 0;
void setup() {
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {

  int value = digitalRead(PIN_BUTTON); // 讀取 Button
  // 1-> 沒按, 0-> 有按
  if(value != preValue) {
    Serial.println(value);
    preValue = value;
  }

}
