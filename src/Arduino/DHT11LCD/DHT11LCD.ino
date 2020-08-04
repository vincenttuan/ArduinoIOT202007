#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>  // 液晶 LCD I2C 版
#define DHTPIN 4     // Digital pin connected to the DHT sensor

LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27或0x3F 這是 LCD 在I2C中的地址, 16,2 表示 LCD 的螢幕大小

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello, DHT!");
}

void loop() {
  delay(2000);
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h, 1);
  Serial.print(F("%  Temperature: "));
  Serial.print(t, 1);
  Serial.print(F("°C "));
  Serial.print(f, 1);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic, 1);
  Serial.print(F("°C "));
  Serial.print(hif, 1);
  Serial.println(F("°F"));
  lcd.setCursor(0, 0);
  lcd.print(t, 1);
  lcd.print("(");
  lcd.print(hic, 1);
  lcd.print(") ");
  lcd.print(h, 1);
  lcd.print("%");
}
