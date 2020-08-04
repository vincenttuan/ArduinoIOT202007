const int BIN_PUZEER = 3; // 蜂鳴器接 3 號腳位
int timeout = 1000;

void setup() {
  pinMode(BIN_PUZEER, OUTPUT);
}

void loop() {
  digitalWrite(BIN_PUZEER, HIGH);
  delay(timeout);
  digitalWrite(BIN_PUZEER, LOW);
  delay(timeout);
}
