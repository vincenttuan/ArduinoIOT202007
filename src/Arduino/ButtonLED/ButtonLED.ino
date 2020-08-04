#define LED_RED    12 // LED 紅 (const 表示不可改變)
#define LED_GREEN  11 // LED 綠 (const 表示不可改變)
#define LED_YELLOW 10 // LED 黃 (const 表示不可改變)
#define LED_WHITE  9  // LED 白 (const 表示不可改變)
#define LED_BLUE   8  // LED 藍 (const 表示不可改變)
#define PIN_BUTTON 7
#define PIN_BUZEER 3
int preValue = 0;
int count_max = 200;
int count = 0;
int timeout = 100;
boolean flag = false;

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_WHITE, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_BUZEER, HIGH);
  
  Serial.begin(9600);
}

void loop() {

  int value = digitalRead(PIN_BUTTON); // 讀取 Button
  // 1-> 沒按, 0-> 有按
  
  if(value == 0) {
    Serial.println(count);
    ++count;
    if(count > count_max) {
      loopLED();
    } 
  }
  if(value != preValue) {
    Serial.println(value);
    preValue = value;
    if(value == 0) {
      flag = true;
      tone(PIN_BUZEER, 1000, 100);
      allTurnOn();
      count = 1;
    } else {
      if(flag) {
        tone(PIN_BUZEER, 500, 100);
        allTurnOff();
      }
      count = 0;
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
