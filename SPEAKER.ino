int SPEAKERPIN = A5;
unsigned long previousMillisSPEAKER;
unsigned long currentMillisSPEAKER;
int ongeduldig = 3;
void setupSPEAKER() {

}

void loopSPEAKER() {
  currentMillisSPEAKER = millis();
 
}

void TIK() {
  tone(SPEAKERPIN, 600, 5);
}

void speakerTIK() {
  if ( currentMillisSPEAKER - previousMillisSPEAKER >= 500 ) {
    previousMillisSPEAKER = currentMillisSPEAKER;
    TIK();
  }
}

void speakerSnel() {
  if ( currentMillisSPEAKER - previousMillisSPEAKER >= 250 ) {
    previousMillisSPEAKER = currentMillisSPEAKER;
    TIK();
  }
}
void speakerOngeduldig() {
  if ( currentMillisSPEAKER - previousMillisSPEAKER >= 250 ) {
    previousMillisSPEAKER = currentMillisSPEAKER;

    if (ongeduldig != 0) {
      TIK();
      ongeduldig--;
    } else {
      ongeduldig = 3;
    }


  }
}
