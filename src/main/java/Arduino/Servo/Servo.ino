#include <Servo.h>
#define SERVOPIN 7

Servo myservo; // 建立Servo物件，控制伺服馬達

void setup() {
  Serial.begin(9600);
  myservo.attach(SERVOPIN); // 連接數位腳位7，伺服馬達的訊號線
  myservo.write(180); // 柵欄起始角度
  
}

void loop() {
  for(int i=180;i>=80;i-=10) {
    myservo.write(i);
    delay(50);
  }
  delay(3000);
  for(int i=80;i<=180;i+=10) {
    myservo.write(i);
    delay(50);
  }
  delay(3000);
  
}
