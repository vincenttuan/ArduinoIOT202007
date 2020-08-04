const int LED_RED    = 12; // LED 紅 (const 表示不可改變)
const int LED_GREEN  = 11; // LED 綠 (const 表示不可改變)
const int LED_YELLOW = 10; // LED 黃 (const 表示不可改變)
int timeout = 50; // 設定延遲 ms  (可改變)

void setup() {
  // 設定 Serial
  Serial.begin(9600);
  // 設定 pin 腳位
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
}

void loop() {
  int pin = random(3) + 10; // 隨機取出 10~12 (pin 為內容可變更的區域變數)
  Serial.println(pin); // 印出 pin 資料
  // 寫入數位資料
  digitalWrite(pin, HIGH); // 開燈
  // 延遲
  delay(timeout);
  digitalWrite(pin, LOW); // 關燈
  
}
