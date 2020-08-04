#include <Timer.h>
#include <Wire.h>
#include <NewPing.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <PMS.h>
#include <SoftwareSerial.h>
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
#define SERVOPIN 7
#define BUTTONPIN 12

#define CDSMAX 200
#define MAX_DISTANCE 200

Timer t;      // 時間物件
float temp;   // 溫度
float humd;   // 濕度
int cdsValue; // cds 資料
int ledOnOff; // 1:HIGH(on), 0:LOW(Off)
int distance; // HCSR04 距離(cm)
char pm25;    // PM2.5
int servoDegree; // Servo 角度

float pre_temp;   // 前一個 溫度
float pre_humd;   // 前一個 濕度
int pre_cdsValue; // 前一個 cds 資料
int pre_ledOnOff; // 前一個 1:HIGH(on), 0:LOW(Off)
int pre_distance; // 前一個 HCSR04 距離(cm)
char pre_pm25; // 前一個 pm25

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

Servo myservo; // 建立Servo物件，控制伺服馬達
int buttonValue = 1; // 按下: 0, 不按: 1
int isOpen = 1; // 0: 關, 1:開

SoftwareSerial pmsSerial(2, 3);
PMS pms(pmsSerial);
PMS::DATA pmsData;

void setup() {
  Serial.begin(9600);

  // 腳位定義
  pinMode(LEDPIN, OUTPUT);
  pinMode(CDSPIN, INPUT_PULLUP);
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(BUZEERPIN, OUTPUT);
  pinMode(BUTTONPIN, INPUT_PULLUP);

  // 設備初始
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:00.0\337C H:00.0%");
  lcd.setCursor(0, 1);
  lcd.print("C:000 L:0 D:000 0");
  myservo.attach(SERVOPIN); // 連接數位腳位7，伺服馬達的訊號線
  myservo.write(180); // 柵欄起始角度
  pmsSerial.begin(9600); // pm25 設備初始

  // 輪詢服務
  t.every(100, cds_read);
  t.every(100, dht_read);
  t.every(100, lcd_display);
  t.every(100, hcsr04_distance);
  t.every(100, rgb_led);
  t.every(50, buzzer_play);
  t.every(50, servo_read);
  t.every(50, pm25_read);
  t.every(500, submitData);
  t.every(50, receData);
}

void loop() {
  t.update();
}

// 接收
void receData() {
  if (Serial.available() > 0) {
    int c = Serial.read();
    if (c != 10) {
      if (c == 49 || c == 48) {
        if (isOpen) {
          for (int i = 180; i >= 80; i -= 10) {
            myservo.write(i);
            delay(50);
            servoDegree = i;
          }
        } else {
          for (int i = 80; i <= 180; i += 10) {
            myservo.write(i);
            delay(50);
            servoDegree = i;
          }
        }
        isOpen = !isOpen;
      }
    }
  }
}

// 傳送
void submitData() {
  Serial.print(temp);   // 溫度
  Serial.print(",");
  Serial.print(humd);   // 濕度
  Serial.print(",");
  Serial.print(cdsValue); // cds 資料
  Serial.print(",");
  Serial.print(ledOnOff); // 1:HIGH(on), 0:LOW(Off)
  Serial.print(",");
  Serial.print(distance); // HCSR04 距離(cm)
  Serial.print(",");
  Serial.print(pm25);
  Serial.print(",");
  Serial.print(servoDegree);
  Serial.println("#");
}

void servo_read() {
  int value = digitalRead(BUTTONPIN); // 讀取 Button

  delay(100);
  if (value == 1) return;
  buttonValue = value;
  if (buttonValue == 0) {
    if (isOpen) {
      for (int i = 180; i >= 80; i -= 10) {
        myservo.write(i);
        delay(50);
        servoDegree = i;
      }
    } else {
      for (int i = 80; i <= 180; i += 10) {
        myservo.write(i);
        delay(50);
        servoDegree = i;
      }
    }
    isOpen = !isOpen;
  }
  delay(1000);
}

void cds_read() {
  cdsValue = analogRead(CDSPIN);
  if (cdsValue > CDSMAX) {
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
  if (distance == 0) {
    analogWrite(REDPIN, 0);
    analogWrite(GREENPIN, 0);
    analogWrite(BLUEPIN, 255);
  } else if (distance < 10) {
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
  if (distance == 0) return;
  if (distance < 10) {
    digitalWrite(BUZEERPIN, HIGH);
    delay(50);
    digitalWrite(BUZEERPIN, LOW);
    delay(50);
  }
}

void lcd_display() {
  // T:00.0\337C H:00.0%
  if (temp != pre_temp) {
    lcd.setCursor(2, 0);
    lcd.print("    ");
    lcd.setCursor(2, 0);
    lcd.print(temp, 1);
    pre_temp = temp;
  }

  if (humd != pre_humd) {
    lcd.setCursor(11, 0);
    lcd.print("    ");
    lcd.setCursor(11, 0);
    lcd.print(humd, 1);
    pre_humd = humd;
  }
  // C:000 L:0 D:000 0
  if (cdsValue != pre_cdsValue) {
    lcd.setCursor(2, 1);
    lcd.print("    ");
    lcd.setCursor(2, 1);
    lcd.print(cdsValue);
    pre_cdsValue = cdsValue;
  }
  if (ledOnOff != pre_ledOnOff) {
    lcd.setCursor(8, 1);
    lcd.print("  ");
    lcd.setCursor(8, 1);
    lcd.print(ledOnOff);
    pre_ledOnOff = ledOnOff;
  }
  if (distance != pre_distance) {
    lcd.setCursor(12, 1);
    lcd.print("   ");
    lcd.setCursor(12, 1);
    lcd.print(distance);
    pre_distance = distance;
  }
  if (pm25 != pre_pm25) {
    lcd.setCursor(15, 1);
    lcd.print(" ");
    lcd.setCursor(15, 1);
    lcd.print(pm25);
    pre_pm25 = pm25;
  }
}

void pm25_read() {
  int value = pms_read_PM2();
  if (value == 0) pm25 = '?';
  else if (value >= 1 && value <= 5) pm25 = 'A';
  else if (value >= 6 && value <= 10) pm25 = 'B';
  else if (value >= 11 && value <= 15) pm25 = 'C';
  else if (value >= 16 && value <= 35) pm25 = 'D';
  else if (value >= 36 && value <= 65) pm25 = 'E';
  else if (value >= 66 && value <= 150) pm25 = 'F';
  else if (value >= 151 && value <= 250) pm25 = 'G';
  else if (value > 251) pm25 = 'H';


  delay(10);
}

int pms_read_PM1()
{
  pms.read(pmsData);
  return pmsData.PM_AE_UG_1_0;
}

int pms_read_PM2()
{
  pms.read(pmsData);
  return pmsData.PM_AE_UG_2_5;
}

int pms_read_PM10()
{
  pms.read(pmsData);
  return pmsData.PM_AE_UG_10_0;
}
