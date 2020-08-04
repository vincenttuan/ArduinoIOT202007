#include <AFMotor.h>
#include <SoftwareSerial.h>
SoftwareSerial BT(9, 10); // 藍芽版的 TX=9, RX=10

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

int init_speed = 150;
int pre_speed = 0;
int speed = init_speed;
boolean isForward = true;
String val = "";
void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  delay(10);
}

void loop() {
  while (BT.available() > 0) {
    val += BT.read();
    delay(2);
  }
  
  if (val.length() > 0) {
    Serial.println(val);
    if(val == "102") { // f
        isForward = true;
        motor1.run(BACKWARD);
        motor2.run(BACKWARD);
        motor3.run(BACKWARD);
        motor4.run(BACKWARD);
        if (speed < init_speed) speed = init_speed;
    } else if(val == "98") { // b
        isForward = false;
        motor1.run(FORWARD);
        motor2.run(FORWARD);
        motor3.run(FORWARD);
        motor4.run(FORWARD);
        if (speed < init_speed) speed = init_speed;
    } else if(val == "108") { // l
        if (isForward) {
          motor1.run(BACKWARD);
          motor2.run(BACKWARD);
          motor3.run(FORWARD);
          motor4.run(FORWARD);
        } else {
          motor1.run(FORWARD);
          motor2.run(FORWARD);
          motor3.run(BACKWARD);
          motor4.run(BACKWARD);
        }
        if (speed < init_speed) speed = init_speed;
    } else if(val == "114") { // r
        if (isForward) {
          motor1.run(FORWARD);
          motor2.run(FORWARD);
          motor3.run(BACKWARD);
          motor4.run(BACKWARD);
        } else {
          motor1.run(BACKWARD);
          motor2.run(BACKWARD);
          motor3.run(FORWARD);
          motor4.run(FORWARD);
        }
    } else if(val == "49") { // 1
        speed += 20;
        if (speed > 255) speed = 255;
    } else if(val == "48") { // 0
        speed -= 20;
        if (speed < 0) speed = 0;
    } else if(val == "112") { // p
        speed = 255;
    } else if(val == "115") { // s
        speed = 0;
    }  
    val = "";
  }
  
  
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);

  if(pre_speed != speed) {
    Serial.println(speed);
    pre_speed = speed;
  }
}
