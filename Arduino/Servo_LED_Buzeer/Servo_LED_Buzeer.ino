#include <Servo.h>
#include <Timer.h>
#define SERVOPIN 7
#define LEDPIN 12
#define BUZZERPIN 8

Servo myservo; // 建立Servo物件，控制伺服馬達
Timer t; // 宣告 Timer 物件
boolean play = false;
int delay_ts = 100;
int delay_ts_sum = 0;
void setup() {
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);
  myservo.attach(SERVOPIN); // 連接數位腳位7，伺服馬達的訊號線
  myservo.write(180); // 柵欄起始角度
  digitalWrite(LEDPIN, HIGH);

  t.every(0, listenerInput);
}

void loop() {
  t.update();
}

void listenerInput() {
  if (Serial.available()) {
    char data = Serial.read();

    if (data == '1') {
      play = true;
      openFences();
      play = false;
    }
  }
}

void openFences() {
  // 開啟柵欄
  for (int i = 180, j = 0; i >= 85; i-=2, j++) {
    myservo.write(i); // 使用write，傳入角度，從0度轉到180度
    delay_ts_sum += delay_ts;
    digitalWrite(LEDPIN, j%2==0);
    digitalWrite(BUZZERPIN, j%2==0);
    delay(50);
  }
  digitalWrite(BUZZERPIN, LOW);
  delay(3000);
  // 關閉柵欄
  for (int i = 85, j = 0; i <= 180; i+=2, j++) {
    myservo.write(i);// 使用write，傳入角度，從180度轉到0度
    digitalWrite(LEDPIN, j%2==0);
    digitalWrite(BUZZERPIN, j%2==0);
    delay(50);
  }
  digitalWrite(LEDPIN, HIGH);
  digitalWrite(BUZZERPIN, LOW);
}
