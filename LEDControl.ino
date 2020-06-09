//hardware pin led array
const int PINARRAY[] = {2,8,9,A2,A3,A4};
//aantal objecten in pinarray
const int AANTALLEDS = sizeof(PINARRAY) / sizeof(int);
//schekd alle pin naar output
void ledControlSetup() {
  for (int i = 0; i < AANTALLEDS; i++) {
    pinMode(PINARRAY[i], OUTPUT);
  }
}
//zet alle led op true
void ledControlTurnAllOn() {
  for (int led = 0; led < AANTALLEDS; led ++) {
    ledControlTurnOn(led);
  }
}
//zet alle led op false
void ledControlTurnAllOff() {
  for (int led = 0; led < AANTALLEDS; led ++) {
    ledControlTurnOff(led);
  }
}
//zet 1 led op true
void ledControlTurnOn(int led) {
  digitalWrite(PINARRAY[led], HIGH);
}
//zet 1 led op false
void ledControlTurnOff(int led) {
  digitalWrite(PINARRAY[led], LOW);
}
//zet 1 led op true, wacht  
void ledControlTurnOn(int led, int vertragingTijd) {
  digitalWrite(PINARRAY[led], HIGH);
  delay(vertragingTijd);
}
//zet 1 led op false, wacht 
void ledControlTurnOff(int led, int vertragingTijd) {
  digitalWrite(PINARRAY[led], LOW);
  delay(vertragingTijd);
}
//zet alle leds uit, zet 1 led aan.
void ledControlTurnAllOffTurnOneOn(int led) {
  ledControlTurnAllOff();
  ledControlTurnOn(led);
}
//return aantalleds
int aantalLeds() {
  return AANTALLEDS;
}
