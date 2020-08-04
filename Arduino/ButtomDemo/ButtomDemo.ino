#define PIN_BUTTON 7

void setup() {
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {

  int value = digitalRead(PIN_BUTTON); // 讀取 Button
  // 1-> 沒按, 0-> 有按
  Serial.println(value);

}
