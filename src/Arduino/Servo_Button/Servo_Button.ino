#include <Servo.h>
#define SERVOPIN 7
#define BUTTONPIN 12

Servo myservo; // 建立Servo物件，控制伺服馬達
int buttonValue = 1; // 按下: 0, 不按: 1
int isOpen = 1; // 0: 關, 1:開

void setup() {
  Serial.begin(9600);
  pinMode(BUTTONPIN, INPUT_PULLUP);
  myservo.attach(SERVOPIN); // 連接數位腳位7，伺服馬達的訊號線
  myservo.write(180); // 柵欄起始角度

}

void loop() {
  int value = digitalRead(BUTTONPIN); // 讀取 Button
  //Serial.println(value);
  delay(100);
  if (value == 1) return;
  buttonValue = value;
  if (buttonValue == 0) {
    Serial.print("isOpen=");
    Serial.println(isOpen);
    if (isOpen) {
      for (int i = 180; i >= 80; i -= 10) {
        myservo.write(i);
        delay(50);
      }
    } else {
      for (int i = 80; i <= 180; i += 10) {
        myservo.write(i);
        delay(50);
      }
    }
    isOpen = !isOpen;
  }
  delay(1000);

}
