#include <Wire.h>
#include <LiquidCrystal_I2C.h>  // NewLiquidCrystal library

#define PIN_LED 11
#define PIN_CDS A3

LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27或0x3F 這是 LCD 在I2C中的地址, 16,2 表示 LCD 的螢幕大小

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_CDS, INPUT_PULLUP);
  
  lcd.init(); // LCD 初始
  lcd.backlight(); // 開啟背光
  lcd.clear(); // 清空 LCD
  lcd.setCursor(0, 0); //Start at character 0 on line 0
  lcd.print("Hello CDS") ;
}

void loop() {
  int cds = analogRead(PIN_CDS)  ;
  Serial.println(cds);
  if(cds >= 200) {
    digitalWrite(PIN_LED, HIGH);
  } else {
    digitalWrite(PIN_LED, LOW);
  }
  lcd.setCursor(0, 1);
  lcd.print("                ") ;
  lcd.setCursor(0, 1);
  lcd.print(cds);
  lcd.setCursor(9, 0);
  lcd.print(".") ;
  delay(1000);
  lcd.setCursor(9, 0);
  lcd.print(" ") ;
  delay(1000);
}
