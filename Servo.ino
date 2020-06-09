//#include <Servo.h>
const int SERVOPIN = 5;
const int SERVOMAX = 180;
const int SERVOMIN = 18;
int servoPostion;
Servo servo;
void setupServo() {
  servo.attach(SERVOPIN);
  servoPostion = SERVOMIN;
  setServo(getServoPostion());
}

void setServo(int i) {
  servoPostion = constrain(i, SERVOMIN, SERVOMAX);
  servo.write(servoPostion);
}

int getServoPostion() {
  return servoPostion;
}

int getServoMax() {
  return SERVOMAX;
}

int getServoMin() {
  return SERVOMIN;
}

int getServoMap(int i) {
  return map(i, 0, 180, SERVOMIN, SERVOMAX);
}
