const int LED_RED    = 12; // LED 紅 (const 表示不可改變)
const int LED_GREEN  = 11; // LED 綠 (const 表示不可改變)
const int LED_YELLOW = 10; // LED 黃 (const 表示不可改變)
const int LED_WHITE  = 9;  // LED 白 (const 表示不可改變)
const int LED_BLUE   = 8;  // LED 藍 (const 表示不可改變)
int timeout = 100; // 設定延遲 ms  (可改變)

void setup() {
  // 設定 Serial
  Serial.begin(9600);
  // 設定 pin 腳位
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_WHITE, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

void loop() {
  // 霹靂燈
  // 8, 9, 10, 11, 12 (遞增輪流亮燈)
  for(int pin=8;pin<=12;pin++) {
    digitalWrite(pin, HIGH);
    delay(timeout);
    digitalWrite(pin, LOW);
  }
  // 11, 10, 9 (遞減輪流亮燈)
  for(int pin=11;pin>=9;pin--) {
    digitalWrite(pin, HIGH);
    delay(timeout);
    digitalWrite(pin, LOW);
  }
  
}
