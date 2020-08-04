int LED_PIN = 12;
void setup() {
  // 設定 pin 腳位
  pinMode(LED_PIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  // 寫入數位資料
  digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  // 延遲
  delay(1000);                       // wait for a second
  digitalWrite(LED_PIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
