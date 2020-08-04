#define PIN_LED 11
#define PIN_CDS A3

int timeout = 5;
void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_CDS, INPUT_PULLUP);
}

void loop() {
  int cds = analogRead(PIN_CDS)  ;
  Serial.println(cds);
  if(cds >= 500) {
    digitalWrite(PIN_LED, HIGH);
  } else {
    digitalWrite(PIN_LED, LOW);
  }

}
