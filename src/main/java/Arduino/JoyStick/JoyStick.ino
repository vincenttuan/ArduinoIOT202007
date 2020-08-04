void setup() {
  Serial.begin(9600);
}
 
void loop() {
  int vrx, vry, sw;
 
  vrx = analogRead(A1);
  vry = analogRead(A2);
  sw = analogRead(A3);
 
  char buf[100];
  sprintf(buf, "VRx=%d, VRy=%d, SW=%d", vrx, vry, sw);
  Serial.println(buf);
  delay(100);
}
