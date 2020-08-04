#include <Timer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTTYPE DHT11
#define DHTPIN 4
#define CDSPIN A3
#define LEDPIN 13
#define CDSMAX 100

Timer t;      // 時間物件
float temp;   // 溫度
float humd;   // 濕度
int cdsValue; // cds 資料
int ledOnOff; // 1:HIGH(on), 0:LOW(Off)
float pre_temp;   // 前一個 溫度
float pre_humd;   // 前一個 濕度
int pre_cdsValue; // 前一個 cds 資料
int pre_ledOnOff; // 前一個 1:HIGH(on), 0:LOW(Off)

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  
  // 腳位定義
  pinMode(LEDPIN, OUTPUT);
  pinMode(CDSPIN, INPUT_PULLUP);

  // 設備初始
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:00.0\337C H:00.0%");
  lcd.setCursor(0, 1);
  lcd.print("C:000 L:0");
  
  // 輪詢服務
  t.every(100, cds_read);
  t.every(100, dht_read);
  t.every(100, lcd_display);
}

void loop() {
  t.update();
}

void cds_read() {
  cdsValue = analogRead(CDSPIN);
  if(cdsValue > CDSMAX) {
    digitalWrite(LEDPIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);  
  }
  ledOnOff = digitalRead(LEDPIN);
}

void dht_read() {
  float hu = dht.readHumidity();
  float te = dht.readTemperature();
  if (isnan(hu) || isnan(te)) {
    return;
  }
  temp = te;
  humd = hu;
}

void lcd_display() {
  // T:00.0\337C H:00.0%
  if(temp != pre_temp) {
    lcd.setCursor(2, 0);
    lcd.print("    ");
    lcd.setCursor(2, 0);
    lcd.print(temp, 1);
    pre_temp = temp;
  }

  if(humd != pre_humd) {
    lcd.setCursor(11, 0);
    lcd.print("    ");
    lcd.setCursor(11, 0);
    lcd.print(humd, 1);
    pre_humd = humd;
  }
  // C:000 L:0
  if(cdsValue != pre_cdsValue) {
    lcd.setCursor(2, 1);
    lcd.print("    ");
    lcd.setCursor(2, 1);
    lcd.print(cdsValue);
    pre_cdsValue = cdsValue;
  }
  if(ledOnOff != pre_ledOnOff) {
    lcd.setCursor(8, 1);
    lcd.print("  ");
    lcd.setCursor(8, 1);
    lcd.print(ledOnOff, 1);
    pre_ledOnOff = ledOnOff;
  }
}
