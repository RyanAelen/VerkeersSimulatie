const int SLAGBOOM_DICHT = 0;
const int SLAGBOOM_OPENEN = 1;
const int SLAGBOOM_OPEN = 2;
const int SLAGBOOM_SLUITEN = 3;
boolean slagBoomIsDicht = false;
boolean slagBoomIsOpen = false;
boolean slagBoomisInBewering = false;
int SLAGBOOMSTATE;
unsigned long currenttimeSLAGBOOM;
unsigned long previousMillisSLAGBOOM;
void setupSlagboom() {
  setupServo();
  setupScherm();
  int SLAGBOOMSTATE = SLAGBOOM_DICHT;
  slagBoomIsDicht = true;
  slagBoomisInBewering = false;
  slagBoomIsOpen = false;

}

void loopSlagBoom(unsigned long currenttime) {
  loopScherm(currenttime);
  slagBoomStateMachine();
  currenttimeSLAGBOOM = currenttime;
  if (schermOpStop()) {
    slagBoomIsOpen = false;
  }
}

void  startSlagboom() {
  slagBoomIsDicht = false;
}

void sluitSlagboom() {
  slagBoomIsOpen = false;
}

boolean getslagboom() {
  return slagBoomIsDicht;
}


void slagBoomStateMachine() {
  switch (SLAGBOOMSTATE) {
    case SLAGBOOM_DICHT: ///Dicht
    
      if (!slagBoomIsDicht || getDagStand()) {
        //slagboom openen gaan.
        SLAGBOOMSTATE = SLAGBOOM_OPENEN;
        slagBoomisInBewering = true;
        slagBoomIsDicht = false;
        previousMillisSLAGBOOM = currenttimeSLAGBOOM;
      }
      break;

    case SLAGBOOM_OPENEN: // Openen
      //    Serial.println("openene");
      if (currenttimeSLAGBOOM - previousMillisSLAGBOOM >= 10) {
        previousMillisSLAGBOOM = currenttimeSLAGBOOM;
        setServo(getServoPostion() + 1);
      }
      if (getServoMax() == getServoPostion()) {
        SLAGBOOMSTATE = SLAGBOOM_OPEN;
        slagBoomisInBewering = false;
        slagBoomIsOpen = true;
        setLopen();
      }
      break;

    case SLAGBOOM_OPEN: // Open
      Serial.println("open");

      
      if (schermOpStop()&&!getDagStand()) {
        //slagboom sluiten gaan.
        SLAGBOOMSTATE = SLAGBOOM_SLUITEN;
        slagBoomisInBewering = true;
        slagBoomIsOpen = false;
        previousMillisSLAGBOOM = currenttimeSLAGBOOM;
      }
      break;

    case SLAGBOOM_SLUITEN:  //Sluiten
      //    Serial.println("sluiten");
      if (currenttimeSLAGBOOM - previousMillisSLAGBOOM >= 10) {
        previousMillisSLAGBOOM = currenttimeSLAGBOOM;
        setServo(getServoPostion() - 1);
      }
      if (getServoMin() == getServoPostion()) {
        SLAGBOOMSTATE = SLAGBOOM_DICHT;
        slagBoomisInBewering = false;
        slagBoomIsDicht = true;
      }
      break;


  }

}
