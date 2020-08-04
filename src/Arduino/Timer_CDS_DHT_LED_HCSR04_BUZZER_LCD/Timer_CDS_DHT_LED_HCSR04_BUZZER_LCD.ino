#include <Timer.h>
#include <Wire.h>
#include <NewPing.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTTYPE DHT11
#define DHTPIN 4
#define CDSPIN A3
#define LEDPIN 13
#define REDPIN 11
#define GREENPIN 10
#define BLUEPIN 9
#define BUZEERPIN 8
#define TRIGGER_PIN  5
#define ECHO_PIN 6

#define CDSMAX 100
#define MAX_DISTANCE 200

Timer t;      // 時間物件
float temp;   // 溫度
float humd;   // 濕度
int cdsValue; // cds 資料
int ledOnOff; // 1:HIGH(on), 0:LOW(Off)
int distance; // HCSR04 距離(cm)

float pre_temp;   // 前一個 溫度
float pre_humd;   // 前一個 濕度
int pre_cdsValue; // 前一個 cds 資料
int pre_ledOnOff; // 前一個 1:HIGH(on), 0:LOW(Off)
int pre_distance; // 前一個 HCSR04 距離(cm)

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
  
  // 腳位定義
  pinMode(LEDPIN, OUTPUT);
  pinMode(CDSPIN, INPUT_PULLUP);
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(BUZEERPIN, OUTPUT);

  // 設備初始
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:00.0\337C H:00.0%");
  lcd.setCursor(0, 1);
  lcd.print("C:000 L:0 D:000");
  
  // 輪詢服務
  t.every(100, cds_read);
  t.every(100, dht_read);
  t.every(100, lcd_display);
  t.every(100, hcsr04_distance);
  t.every(100, rgb_led);
  t.every(50, buzzer_play);
  
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

void hcsr04_distance() {
  distance = sonar.ping_cm();
}

void rgb_led() {
  if(distance == 0) {
    analogWrite(REDPIN, 0);
    analogWrite(GREENPIN, 0);
    analogWrite(BLUEPIN, 255);  
  } else if(distance < 10) {
    analogWrite(REDPIN, 255);
    analogWrite(GREENPIN, 0);
    analogWrite(BLUEPIN, 0);
  } else {
    analogWrite(REDPIN, 0);
    analogWrite(GREENPIN, 255);
    analogWrite(BLUEPIN, 0);
  }
  
}

void buzzer_play() {
  if(distance == 0) return;
  if(distance < 10) {
    digitalWrite(BUZEERPIN, HIGH);
    delay(50);
    digitalWrite(BUZEERPIN, LOW);
    delay(50);
  }
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
  // C:000 L:0 D:000
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
    lcd.print(ledOnOff);
    pre_ledOnOff = ledOnOff;
  }
  if(distance != pre_distance) {
    lcd.setCursor(12, 1);
    lcd.print("   ");
    lcd.setCursor(12, 1);
    lcd.print(distance);
    pre_distance = distance;
  }
}
