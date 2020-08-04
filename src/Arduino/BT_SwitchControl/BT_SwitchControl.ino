#include <SoftwareSerial.h>
#define LEDPIN 13
SoftwareSerial BT(9, 10); // 藍芽版的 TX=9, RX=10
String val = "";
void setup() {
  Serial.begin(9600);
  Serial.println("BT is ready!");
  pinMode(LEDPIN, OUTPUT);
  BT.begin(9600);
  delay(10);
}
void loop() {
  
  while (BT.available() > 0) {
    val += BT.read();
    delay(2);
  }
  
  if (val.length() > 0) {
    Serial.println(val);
    if(val == "48") {
      Serial.println("off");
      digitalWrite(LEDPIN, LOW);  
    } else if (val == "49") {
      Serial.println("on");  
      digitalWrite(LEDPIN, HIGH);  
    }
    val = "";
  }
}
