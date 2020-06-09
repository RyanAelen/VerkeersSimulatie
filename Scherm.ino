byte hexcijvers[] = {0xFC, 0x90, 0x7A, 0xDA, 0x96, 0xCE, 0xEE, 0x98, 0xFE, 0xDE, 0xBE, 0xE6, 0x6C, 0xF2, 0x6E, 0x2E};
byte lopen = 0x64;
byte stoppen = 0xCE;
int schermState;
const int STOP = 0;
const int LOPEN = 1;
const int AFTELLEN = 2;
const int Nachtstand =3;
unsigned long previousMillisScherm;
unsigned long currentMillisScherm;
int teller = 4;
boolean slagBoomOpenen = false;
void setupScherm() {
  setupShiftRegister();
  clearShiftRegister();
  slagBoomOpenen = false;
  schermState = STOP;
  setShiftRegister(stoppen);
}

void setLopen() {
  slagBoomOpenen = true;

}


void loopScherm(unsigned long tijd) {
  currentMillisScherm = tijd;
  schermStateMacine();
  loopSPEAKER();
}


boolean schermOpStop() {
  if (schermState == STOP) {
    return true;
  }
  return false;
}


void schermStateMacine() {
  switch (schermState) {
    case STOP:
      speakerTIK();
      //      Serial.println("STOP");
      if (getDagStand()) {
        schermState = Nachtstand;
        break;
      }
      if (slagBoomOpenen) {
        schermState = LOPEN;
        setShiftRegister(lopen);
        previousMillisScherm = currentMillisScherm;
      }
      break;
    case LOPEN:
      speakerSnel();
      Serial.println("LOPEN");
      //timmer 30 sec
      if (currentMillisScherm - previousMillisScherm >= 1000) {
        previousMillisScherm = currentMillisScherm;
        //naar aftellen
        schermState = AFTELLEN;
      }

      break;
    case AFTELLEN:
      Serial.println("AFTELLEN");
      speakerOngeduldig();
      if (currentMillisScherm - previousMillisScherm >= 1000) {
        previousMillisScherm = currentMillisScherm;
        setShiftRegister(hexcijvers[teller]);
        teller--;
      }
      if (teller == -1) {
        schermState = STOP;
        setShiftRegister(stoppen);
        teller = 4;
        slagBoomOpenen = false;
      }


      break;
    case Nachtstand:
      if (!getDagStand()) {
        schermState = STOP;
      }
      break;
  }

}
