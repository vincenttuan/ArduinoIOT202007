#include <Timer.h>
#define LED_PIN 13

Timer t; //宣告 Timer 物件
double temp;
double humd;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  // 輪詢服務
  t.every(500, dht);
  t.every(100, receData);
  t.every(1000, submitData);
}

void loop() {
  t.update();
}

void dht() {
  temp = random(20, 30);
  humd = random(50, 80);
}


// 接收
void receData() {
  if(Serial.available() > 0) {
    int c = Serial.read();
    if (c != 10) {
      if(c == 49) digitalWrite(LED_PIN, HIGH);
      else if(c == 48) digitalWrite(LED_PIN, LOW);
    }
  }
}

// 傳送
void submitData() {
    Serial.print(temp);
    Serial.print(",");
    Serial.print(humd);
    Serial.println("#");
}
