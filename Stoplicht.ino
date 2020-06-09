const int ROOD = 0;
const int GEEL = 1;
const int GROEN = 2;
const int KNIPPER = 3;
const int LICHTEN[] = {ROOD, GEEL, GROEN};
const int AANTALSTOPLICHT = 2;
int stoplight_STATE[AANTALSTOPLICHT];
const int TIENSEC = 10000;
const int EENSEC = 1000;
const int STOPLICHTEN[2][3] = {{0, 1, 2}, {3, 4, 5}};
unsigned long currentStoplichtTimer;
unsigned long previousMillisStoplichtTimer[AANTALSTOPLICHT];
boolean aanDeBeurd[2];
boolean stoplichtknipper[2];

void setupStopLicht() {
  for (int i = 0; i < AANTALSTOPLICHT; i++) {
    stoplight_STATE[i] = ROOD;
    ROODLedAan(i);
  }
}

void loopStoplicht(int i) {
  stoplichtStateMachine();
  currentStoplichtTimer = i;
}

void startStopLicht(int i) {
  aanDeBeurd[i] = true;
}

boolean getStoplichtStatus(int i) {
  if (stoplight_STATE[i] == ROOD) {
    return false;
  } else {
    return true;
  }

}

void stoplichtStateMachine() {
  for (int i = 0; i < AANTALSTOPLICHT; i++) {
    switch (stoplight_STATE[i]) {
      case ROOD:

        //      Serial.print("rood");
        //      Serial.print(": "); Serial.print(i);Serial.println();
        //      ROODLedAan(i);
        //is aan de beurt
        if (getDagStand()) {
          ROODLedUit(i);
          stoplight_STATE[i] = KNIPPER;
          previousMillisStoplichtTimer[i] = currentStoplichtTimer;
          break;
        }
        if (aanDeBeurd[i]) {
          ROODLedUit(i);
          stoplight_STATE[i] = GROEN;
          previousMillisStoplichtTimer[i] = currentStoplichtTimer;
          GROENLedAan(i);
          break;
        }
        break;
      case GEEL:
        //      GEELLedAan(i);
        //timmer 1 sec
        if (currentStoplichtTimer - previousMillisStoplichtTimer[i] >= EENSEC) {
          previousMillisStoplichtTimer[i] = currentStoplichtTimer;
          //ga naar rood
          GEELLedUit(i);
          stoplight_STATE[i] = ROOD;
          ROODLedAan(i);
        }
        break;
      case GROEN:
        //      GROENLedAan(i);
        //timmer 10 sec
        if (currentStoplichtTimer - previousMillisStoplichtTimer[i] >= 2000) {
          previousMillisStoplichtTimer[i] = currentStoplichtTimer;
          //ga naar geel
          GROENLedUit(i);
          stoplight_STATE[i] = GEEL;
          GEELLedAan(i);
        }
        break;
      case KNIPPER:
        if (!getDagStand()) {
          GEELLedUit(i);
          stoplight_STATE[i] = ROOD;
          ROODLedAan(i);
        }
        if (currentStoplichtTimer - previousMillisStoplichtTimer[i] >= 2000) {
          previousMillisStoplichtTimer[i] = currentStoplichtTimer;
          stoplichtknipper[i] = !stoplichtknipper[i];
          if (stoplichtknipper[i]) {
            GEELLedAan(i);
          } else {
            GEELLedUit(i);
          }
        }
    }

  }
}

//ROOD
void ROODLedAan(int stoplicht) {
  ledControlTurnOn(STOPLICHTEN[stoplicht][ROOD]);
  aanDeBeurd[stoplicht] = false;
}
void ROODLedUit(int stoplicht) {
  ledControlTurnOff(STOPLICHTEN[stoplicht][ROOD]);
}
//GEEL
void GEELLedAan(int stoplicht) {
  ledControlTurnOn(STOPLICHTEN[stoplicht][GEEL]);
}
void GEELLedUit(int stoplicht) {
  ledControlTurnOff(STOPLICHTEN[stoplicht][GEEL]);
}
//GROEN
void GROENLedAan(int stoplicht) {
  ledControlTurnOn(STOPLICHTEN[stoplicht][GROEN]);
}
void GROENLedUit(int stoplicht) {
  ledControlTurnOff(STOPLICHTEN[stoplicht][GROEN]);
}
