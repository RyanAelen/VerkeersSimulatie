int dataPin = 3;
int clockPin = 4;
int latchPin = 6;
void setupShiftRegister() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
void clearShiftRegister() {
  setShiftRegister(0x0);
}
void allOnShiftRegister() {
  setShiftRegister(0xff);
}

void setShiftRegister(byte pattern) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(dataPin, !!(pattern & (1 << (7 - i))));
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
  }
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin, LOW);
}
