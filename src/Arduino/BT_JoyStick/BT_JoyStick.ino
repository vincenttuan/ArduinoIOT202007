#include <SoftwareSerial.h>
// 定義連接藍牙模組的序列埠
SoftwareSerial BT(9, 10); // 接收腳 (對應藍芽版的TX9), 傳送腳 (對應藍芽版的RX10)
char val;  // 儲存接收資料的變數

int sw_count = 0;
void setup() {
  Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("BT is ready!");

  BT.begin(9600);
}

void loop() {
  int vrx, vry, sw;
  vrx = analogRead(A1);
  vry = analogRead(A2);
  sw = analogRead(A3);
  if (vrx < 450) {
    Serial.println("l");
    BT.print('l');
  }
  if (vrx > 550) {
    Serial.println("r");
    BT.print('r');
  }
  if (vry < 450) {
    Serial.println("f");
    BT.print('f');
  }
  if (vry > 550) {
    Serial.println("b");
    BT.print('b');
  }
  if ((vrx > 450 && vrx < 550) && ((vry > 450 && vry < 550))) {
    //Serial.println("");
  }
  if (sw == 0) { // 按下去
    sw_count++;
  } else { // 放開
    if (sw_count > 1 && sw_count < 10) {
      Serial.println("1"); // 短按
      BT.print('1');
    }
    else if (sw_count > 10) {
      Serial.println("s"); // 長按
      BT.print('s');
      sw_count = 0;
    }
  }


  delay(100);

}
