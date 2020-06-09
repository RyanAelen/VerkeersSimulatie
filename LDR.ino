const int LDRPIN = A1;
void LDRSetup() {
  pinMode(LDRPIN, INPUT);
}
void printLDR() {
  int ldrValue = analogRead(LDRPIN);
  int ldrLux = map(ldrValue, 0 , 1023, 500, 0);
  Serial.println(ldrLux);
}

int getLDR() {
  int ldrValue = analogRead(LDRPIN);
  int ldrLux = map(ldrValue, 0 , 1023, 500, 0);
  return ldrLux;
}
