void setup() {
  Serial.begin(9600);
  Serial.println("Please input something...");
}

void loop() {
  if(Serial.available() > 0) { // 是否要資料傳入 ?
    //String data = Serial.readString(); // 讀取字串
    char data = Serial.read(); // 讀取字元
    if(data != '\n') { // 不處理斷行字元
      Serial.print("Arduino:");
      Serial.println(data); // 回應說, Arduino 接到資料了, 資料是 data...
    }
  }

}
