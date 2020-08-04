#define PIN_LED 11
#define PIN_CDS A3

int timeout = 5;
void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_CDS, INPUT_PULLUP);
}

void loop() {
  for(int i=0;i<255;i++) {
    analogWrite(PIN_LED, i);
    if( i % 50 == 0) {
      int cds = analogRead(PIN_CDS)  ;
      Serial.println(cds);
    }
    delay(timeout);  
  }
  for(int i=255;i>=0;i--) {
    analogWrite(PIN_LED, i);
    if( i % 50 == 0) {
      int cds = analogRead(PIN_CDS)  ;
      Serial.println(cds);
    }
    delay(timeout);  
  }
  
}
