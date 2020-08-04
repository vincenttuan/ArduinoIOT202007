/***********************************************************
 * I2C LCD 接線說明
 * SDA – 接 Arduino 的 A4
 * SCL – 接 Arduino 的 A5
 * GND – 接 GND
 * VCC – 接 +5V
 ***********************************************************/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>  // 液晶 LCD I2C 版

// 定義 LCD 的規格設定
LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27或0x3F 這是 LCD 在I2C中的地址, 16,2 表示 LCD 的螢幕大小

void setup() {
  lcd.init(); // 初始化
  lcd.backlight(); // 開啟背光
  lcd.clear(); // 清空 LCD
  lcd.setCursor(0, 0); // 放置的位置(x, y) 例如: (0, 0) 第一行, (0, 1) 第二行
  lcd.print("Hello, LCD!");
}

void loop() {

}
