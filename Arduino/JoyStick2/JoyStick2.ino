void setup() {
  Serial.begin(9600);
}

int sw_count = 0;
void loop() {
  int vrx, vry, sw;

  vrx = analogRead(A1);
  vry = analogRead(A2);
  sw = analogRead(A3);

  char buf[100];
  sprintf(buf, "VRx=%d, VRy=%d, SW=%d", vrx, vry, sw);
  //Serial.println(buf);
  if (vrx < 450) Serial.println("l");
  if (vrx > 550) Serial.println("r");
  if (vry < 450) Serial.println("f");
  if (vry > 550) Serial.println("b");
  if ((vrx > 450 && vrx < 550) && ((vry > 450 && vry < 550))) {
    //Serial.println("");
  }
  if (sw == 0) { // 按下去
    sw_count++;
  } else { // 放開
    if (sw_count > 1 && sw_count < 10)
      Serial.println("1"); // 短按
    else if (sw_count > 10)
      Serial.println("s"); // 長按
    sw_count = 0;
  }


  delay(50);
}
