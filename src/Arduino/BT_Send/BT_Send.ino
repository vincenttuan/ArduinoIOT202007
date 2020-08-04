#include <SoftwareSerial.h>
// https://www.taiwaniot.com.tw/wp-content/uploads/2016/01/ADIO-HC-05-1.pdf
// 定義連接藍牙模組的序列埠
SoftwareSerial BT(9, 10); // 接收腳 (對應藍芽版的TX9), 傳送腳 (對應藍芽版的RX10)
char val;  // 儲存接收資料的變數
 
void setup() {
  Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("BT is ready!");
 
  BT.begin(9600);
}
 
void loop() {
  if(Serial.available() > 0) {
    char data = Serial.read();
    Serial.println(data);  
    BT.print(data);
  }
}
