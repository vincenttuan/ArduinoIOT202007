#define LED_RED    12 // LED 紅 (const 表示不可改變)
#define LED_GREEN  11 // LED 綠 (const 表示不可改變)
#define LED_YELLOW 10 // LED 黃 (const 表示不可改變)
#define LED_WHITE  9  // LED 白 (const 表示不可改變)
#define LED_BLUE   8  // LED 藍 (const 表示不可改變)
#define PIN_BUZEER 3
#define Do  523
#define Re  587
#define Mi  659
#define Fa  698
#define So  784
#define La  880
#define Si  988
int to = 200; // 設定延遲 ms  (可改變)
/*
５３３　４２２　１２３４５５５　
５３３　４２２　１３５５３３３　
２２２２２３４　３３３３３４５　
５３３　４２２　１３５５１
*/
int frequences[] = {
        So, Mi, Mi,  0, Fa, Re, Re,  0, Do, Re, Mi, Fa, So, So, So, 0,
        So, Mi, Mi,  0, Fa, Re, Re,  0, Do, Mi, So, So, Mi, Mi, Mi, 0,
        Re, Re, Re, Re, Re, Mi, Fa,  0, Mi, Mi, Mi, Mi, Mi, Fa, So, 0,
        So, Mi, Mi,  0, Fa, Re, Re,  0, Do, Mi, So, So, Do,
      };
int timeout[]    = {
        to, to, to*1.5, to/2, to, to, to*1.5, to/2, to, to, to, to, to, to, to, to/2,
        to, to, to*1.5, to/2, to, to, to*1.5, to/2, to, to, to, to, to, to, to, to/2,
        to, to, to, to, to, to, to, to/2, to, to, to, to, to, to, to, to/2,
        to, to, to*1.5, to/2, to, to, to*1.5, to/2, to, to, to, to, to*2,
      };                  


void setup() {
  // 設定 Serial
  Serial.begin(9600);
  // 設定 pin 腳位
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_WHITE, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  pinMode(PIN_BUZEER, HIGH);

  for(int i = 0; i < 61 ; i++) {
    allTurnOff();
    switch(frequences[i]) {
        case Do:
          digitalWrite(8, HIGH);
          break;
        case Re:
          digitalWrite(9, HIGH);
          break;
        case Mi:
          digitalWrite(10, HIGH);
          break;
        case Fa:
          digitalWrite(11, HIGH);
          break;
        case So:
          digitalWrite(12, HIGH);
          break;
                  
    }
    tone(PIN_BUZEER, frequences[i], timeout[i]);
    delay(to);
  }
}

void loop() {
  
}

// 全部熄滅
void allTurnOff() {
  for (int pin = 8; pin <= 12; pin++) {
    digitalWrite(pin, LOW);
  }
}
