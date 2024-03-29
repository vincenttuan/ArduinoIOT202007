#include <SoftwareSerial.h>
// https://www.taiwaniot.com.tw/wp-content/uploads/2016/01/ADIO-HC-05-1.pdf
// 定義連接藍牙模組的序列埠
SoftwareSerial BT(9, 10); // 接收腳 (對應藍芽版的TX 9), 傳送腳 (對應藍芽版的RX 10)
char val;  // 儲存接收資料的變數
 
void setup() {
  Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("BT is ready!");
 
  // 設定藍牙模組的連線速率
  // 如果是HC-05，請改成38400
  BT.begin(38400);
}
 
void loop() {
  // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
  if (Serial.available()) {
    val = Serial.read();
    BT.print(val);
  }
 
  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  if (BT.available()) {
    val = BT.read();
    Serial.print(val);
  }
}
