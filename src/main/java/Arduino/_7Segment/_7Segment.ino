// 七段顯示器製作倒數功能 (v1)
/*
  2 
7   3
  8
6   4
  5   9
*/
#define PIN_BUZZER 10
void setup() {               
  pinMode(2, OUTPUT);  
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(9, 0);  // 關閉小數點
}

void loop() {
  // 顯示數字 '9'
  digitalWrite(2, 1);
  digitalWrite(3, 1);
  digitalWrite(4, 1);
  digitalWrite(5, 0);
  digitalWrite(6, 0);
  digitalWrite(7, 1);
  digitalWrite(8, 1);
  delay(1000);
  // 顯示數字 '8'
  digitalWrite(2, 1);
  digitalWrite(3, 1);
  digitalWrite(4, 1);
  digitalWrite(5, 1);
  digitalWrite(6, 1);
  digitalWrite(7, 1);
  digitalWrite(8, 1);
  delay(1000);
  // 顯示數字 '7'
  digitalWrite(2, 1);
  digitalWrite(3, 1);
  digitalWrite(4, 1);
  digitalWrite(5, 0);
  digitalWrite(6, 0);
  digitalWrite(7, 0);
  digitalWrite(8, 0);
  delay(1000);
  // 顯示數字 '6'
  digitalWrite(2, 1);
  digitalWrite(3, 0);
  digitalWrite(4, 1);
  digitalWrite(5, 1);
  digitalWrite(6, 1);
  digitalWrite(7, 1);
  digitalWrite(8, 1);
  delay(1000);
  // 顯示數字 '5'
  digitalWrite(2, 1);
  digitalWrite(3, 0);
  digitalWrite(4, 1);
  digitalWrite(5, 1);
  digitalWrite(6, 0);
  digitalWrite(7, 1);
  digitalWrite(8, 1);
  delay(1000);
  // 顯示數字 '4'
  digitalWrite(2, 0);
  digitalWrite(3, 1);
  digitalWrite(4, 1);
  digitalWrite(5, 0);
  digitalWrite(6, 0);
  digitalWrite(7, 1);
  digitalWrite(8, 1);
  delay(1000);
  // 顯示數字 '3'
  digitalWrite(2, 1);
  digitalWrite(3, 1);
  digitalWrite(4, 1);
  digitalWrite(5, 1);
  digitalWrite(6, 0);
  digitalWrite(7, 0);
  digitalWrite(8, 1);
  tone(PIN_BUZZER, 500, 500);
  delay(1000);
  // 顯示數字 '2'
  digitalWrite(2, 1);
  digitalWrite(3, 1);
  digitalWrite(4, 0);
  digitalWrite(5, 1);
  digitalWrite(6, 1);
  digitalWrite(7, 0);
  digitalWrite(8, 1);
  tone(PIN_BUZZER, 500, 500);
  delay(1000);
  // 顯示數字 '1'
  digitalWrite(2, 0);
  digitalWrite(3, 1);
  digitalWrite(4, 1);
  digitalWrite(5, 0);
  digitalWrite(6, 0);
  digitalWrite(7, 0);
  digitalWrite(8, 0);
  tone(PIN_BUZZER, 500, 500);
  delay(1000);
  // 顯示數字 '0'
  digitalWrite(2, 1);
  digitalWrite(3, 1);
  digitalWrite(4, 1);
  digitalWrite(5, 1);
  digitalWrite(6, 1);
  digitalWrite(7, 1);
  digitalWrite(8, 0);  
  // 暫停 2 秒鐘
  tone(PIN_BUZZER, 1000, 1000);
  delay(2000);
}
