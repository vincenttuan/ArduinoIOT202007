#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27或0x3F 這是 LCD 在I2C中的地址, 16,2 表示 LCD 的螢幕大小
String text = "A";

void setup() {
  Serial.begin(9600);
  lcd.init(); // LCD 初始
  lcd.backlight(); // 開啟背光
  lcd.clear(); // 清空 LCD
  lcd.setCursor(0, 0); //Start at character 0 on line 0
  lcd.print("Ready") ;
  //delay(1000);
}

void loop() {
  marquee(500);
}

// 監聽文字
void listenText() {
  if(Serial.available() > 0) {
    text = Serial.readString();  
    text.trim();
  }
}

// 跑馬燈
void marquee(int timeout) {
  for(int i=0;;i=++i%16) {
    lcd.clear();
    lcd.setCursor(i, 0);
    lcd.print(text);
    delay(timeout);
    listenText(); // 監聽文字
  }
}
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27或0x3F 這是 LCD 在I2C中的地址, 16,2 表示 LCD 的螢幕大小
String text = "A";

void setup() {
  Serial.begin(9600);
  lcd.init(); // LCD 初始
  lcd.backlight(); // 開啟背光
  lcd.clear(); // 清空 LCD
  lcd.setCursor(0, 0); //Start at character 0 on line 0
  lcd.print("Ready") ;
  //delay(1000);
}

void loop() {
  marquee(500);
}

// 監聽文字
void listenText() {
  if(Serial.available() > 0) {
    text = Serial.readString();  
    text.trim();
  }
}

// 跑馬燈
void marquee(int timeout) {
  for(int i=0;;i=++i%16) {
    lcd.clear();
    lcd.setCursor(i, 0);
    lcd.print(text);
    delay(timeout);
    listenText(); // 監聽文字
  }
}
