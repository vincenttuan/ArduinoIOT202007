#include <SPI.h>
#include <RFID.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "iot-pcschool.firebaseio.com"
#define FIREBASE_AUTH ""
#define WIFI_SSID "Gjun207"
#define WIFI_PASSWORD "Gjun@3474878"

#define RST_PIN 15   // D8
#define SS_PIN 2     // D4
#define BUZZER_PIN 5 // D1
#define LED_PIN 16 // D0
#define REED_PIN 4 // D2
const int servoPin = D3;

Servo myservo; // 建立Servo物件，控制伺服馬達
RFID rfid(SS_PIN, RST_PIN);
void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  //Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.begin(FIREBASE_HOST);
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(REED_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  myservo.attach(servoPin);
  myservo.write(0);
  SPI.begin();
  rfid.init();
  delay(100);
  Serial.println("RFID/NFC Ready !");
}
void loop() {
  if (rfid.isCard() && rfid.readCardSerial()) {
    int serNumLength = 5; // rfid.serNum[0] ~ rfid.serNum[4] 共五組
    Serial.println("Card found");
    Serial.println("Card ID:");
    // 將卡號上傳
    Firebase.setInt("rfid/number", rfid.serNum[0]);
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
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println(rfid.serNum[0]);
    if(checkId(rfid.serNum[0])) {
      openTheDoor();
    } else {
        for(int i=0;i<3;i++) {
          digitalWrite(BUZZER_PIN, HIGH);
          delay(100);
          digitalWrite(BUZZER_PIN, LOW);
          delay(100);
        }
        
    }
    delay(1000);
  }
  rfid.halt();  // 命令卡片進入休眠狀態
}

boolean checkId(int id1) {
  int passNumber = Firebase.getInt("rfid/passNumber");
  int balance = Firebase.getInt("rfid/balance");
  if(id1 == passNumber && balance >= 30) {
    Firebase.setInt("rfid/balance", balance-=30);
    Firebase.setInt("myhouse/open", 1);
    return true;    
  } else {
    return false;
  }
}

void openTheDoor() {
  digitalWrite(LED_PIN, HIGH);
  for(int i=0;i<=180;i+=10) {
    myservo.write(i);
    delay(10);
  }
  delay(3000);
  for(int i=180;i>=0;i-=10) {
    myservo.write(i);
    delay(10);
  }
  digitalWrite(LED_PIN, LOW);
}
