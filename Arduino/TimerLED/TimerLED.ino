#include <Timer.h>
#define LED_13 13
#define LED_12 12
#define LED_11 11

Timer t; //宣告 Timer 物件

void setup() {
  Serial.begin(9600);
  pinMode(LED_13, OUTPUT);
  pinMode(LED_12, OUTPUT);
  pinMode(LED_11, OUTPUT);

  t.oscillate(LED_13, 200, LOW);
  t.oscillate(LED_12, 1000, LOW);
  t.oscillate(LED_11, 5000, LOW);
}

void loop() {
  t.update();  
}
