#include <SoftwareSerial.h>
SoftwareSerial BT(9, 10); // 藍芽版的 TX=9, RX=10
String val = "";
void setup() {
  Serial.begin(9600);
  Serial.println("BT is ready!");
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
    val = "";
  }
}
