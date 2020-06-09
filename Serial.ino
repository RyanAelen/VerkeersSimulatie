int serialSpeed = 9600;

void serialSetup() {
  Serial.begin(serialSpeed);
}

void clearSerial() {
  while (Serial.available() > 0) {
    Serial.read();
  }
}

char checkInput() {
  char karakter = 'x';
  if (Serial.available() > 0) {
    karakter = Serial.read();
    clearSerial();
  }
  return karakter;
}
