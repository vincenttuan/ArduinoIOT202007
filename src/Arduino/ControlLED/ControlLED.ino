const int LED_RED    = 12; // LED 紅 (const 表示不可改變)
const int LED_GREEN  = 11; // LED 綠 (const 表示不可改變)
const int LED_YELLOW = 10; // LED 黃 (const 表示不可改變)
const int LED_WHITE  = 9;  // LED 白 (const 表示不可改變)
const int LED_BLUE   = 8;  // LED 藍 (const 表示不可改變)
int timeout = 100;
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
  if (Serial.available() > 0) {
    char n = Serial.read();
    if (n != '\n') {
      Serial.println(n);
      switch (n) {
        case '1':
          turnOnOffLED(12);
          break;
        case '2':
          turnOnOffLED(11);
          break;
        case '3':
          turnOnOffLED(10);
          break;
        case '4':
          turnOnOffLED(9);
          break;
        case '5':
          turnOnOffLED(8);
          break;
        case '6':
          allTurnOff();
          delay(timeout);
          randomLED(); // Random 燈
          break;
        case '7':
          allTurnOff();
          delay(timeout);
          loopLED(); // 霹靂燈
          break;
        case '8': // 全部點亮
          allTurnOn();
          break;
        case '9': // 全部熄滅
          allTurnOff();
          break;
      }
    }
  }
}

// 全部點亮
void allTurnOn() {
  for (int pin = 8; pin <= 12; pin++) {
    digitalWrite(pin, HIGH);
  }
}

// 全部熄滅
void allTurnOff() {
  for (int pin = 8; pin <= 12; pin++) {
    digitalWrite(pin, LOW);
  }
}

// 霹靂燈
void loopLED() {
  // 8, 9, 10, 11, 12 (遞增輪流亮燈)
  for (int pin = 8; pin <= 12; pin++) {
    digitalWrite(pin, HIGH);
    delay(timeout);
    digitalWrite(pin, LOW);
  }
  // 11, 10, 9 (遞減輪流亮燈)
  for (int pin = 11; pin >= 9; pin--) {
    digitalWrite(pin, HIGH);
    delay(timeout);
    digitalWrite(pin, LOW);
  }
}

void randomLED() {
  int pin = random(8, 13);
  Serial.println(pin); // 印出 pin 資料
  // 寫入數位資料
  digitalWrite(pin, HIGH); // 開燈
}

void turnOnOffLED(int pin) {
  digitalWrite(pin, !digitalRead(pin));
}
