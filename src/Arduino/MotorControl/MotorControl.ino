#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

int init_speed = 150;
int pre_speed = 0;
int speed = init_speed;
boolean isForward = true;

void setup() {
  Serial.begin(9600);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void loop() {

  if (Serial.available() > 0) {
    char c = Serial.read();
    switch (c) {
      case 'f': // 102
        isForward = true;
        motor1.run(BACKWARD);
        motor2.run(BACKWARD);
        motor3.run(BACKWARD);
        motor4.run(BACKWARD);
        if (speed < init_speed) speed = init_speed;
        break;
      case 'b': // 98
        isForward = false;
        motor1.run(FORWARD);
        motor2.run(FORWARD);
        motor3.run(FORWARD);
        motor4.run(FORWARD);
        if (speed < init_speed) speed = init_speed;
        break;
      case 'l': // 108
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
        break;
      case 'r': // 114
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
        break;
      case '1': // 49
        speed += 20;
        if (speed > 255) speed = 255;
        break;
      case '0': // 48
        speed -= 20;
        if (speed < 255) speed = 0;
        break;
      case 'p': // 112
        speed = 255;
        break;
      case 's': // 115
        speed = 0;
        break;
    }
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
