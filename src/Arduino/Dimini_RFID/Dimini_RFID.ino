#include <SPI.h>
#include <RFID.h>
#define RST_PIN 15   // D8
#define SS_PIN 2     // D4
#define BUZZER_PIN 5 // D1

RFID rfid(SS_PIN, RST_PIN);
void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  SPI.begin();
  rfid.init();
  delay(100);
  Serial.println("RFID/NFC Ready !");
}
void loop() {
  if (rfid.isCard() && rfid.readCardSerial()) {
    digitalWrite(BUZZER_PIN, HIGH);
    int serNumLength = 5; // rfid.serNum[0] ~ rfid.serNum[4] 共五組
    Serial.println("Card found");
    Serial.println("Card ID:");
    Serial.print("Dec: ");
    for (int i = 0; i < serNumLength; i++) {
      Serial.print(rfid.serNum[i], DEC); // 十進位
      Serial.print(", ");
    }
    Serial.println();
    Serial.print("Hex: ");
    for (int i = 0; i < serNumLength; i++) {
      Serial.print(rfid.serNum[i], HEX); // 十六進位
      Serial.print(", ");
    }
    Serial.println("\r\n");
    delay(150);
    digitalWrite(BUZZER_PIN, LOW);
    delay(1000);
  }
  rfid.halt();  // 命令卡片進入休眠狀態
}
