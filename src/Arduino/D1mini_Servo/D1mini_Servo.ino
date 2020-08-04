#include <Servo.h>
const int servoPin = D3;


Servo myservo; // 建立Servo物件，控制伺服馬達

void setup() {
  Serial.begin(9600);
  myservo.attach(servoPin); // 連接數位腳位D3，伺服馬達的訊號線
  myservo.write(0); // 柵欄起始角度
  
}

void loop() {
  for(int i=0;i<=180;i+=10) {
    myservo.write(i);
    delay(10);
  }
  delay(3000);
  for(int i=180;i>=0;i-=10) {
    myservo.write(i);
    delay(10);
  }
  delay(3000);
}
