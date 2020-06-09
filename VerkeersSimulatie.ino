#include <Servo.h>
unsigned long currentMillis;
unsigned long previousMillis;
unsigned long previousMillisQ;
int verkeersState;
const int START = 0;
const int DodeTijd = 1;
const int STOPLICHTEEN = 2;
const int STOPLICHTTWEE = 3;
const int VEKEERSLAGBOOM = 4;
const int QUEUE = 5;
const int NACHT = 6;
int getqueue;

void setup() {
  serialSetup();
  ledControlSetup();
  setupBUTTONS();
  setupStand();
  Serial.println("v0.09");
  setupStopLicht();
  setupSlagboom();
  verkeersState = START;

}

void loop() {
  currentMillis = millis();
  loopBUTTONS(currentMillis);
  loopqueue();
  loopStand();
  //  test();
  printQueue();
  loopStoplicht(currentMillis);
  verkeerregelaar(currentMillis);
  loopSlagBoom(currentMillis);
}

void verkeerregelaar(int currentMillis) {
  switch (verkeersState) {
    case START:
      exit_Start();
      verkeersState = DodeTijd;
      entry_dodeTijd();
      break;
    case DodeTijd:
      if (currentMillis - previousMillis >= 1000) {
        exit_dodetijd();
        verkeersState = QUEUE;
        enter_queue();
      }
      break;
    case STOPLICHTEEN:
      if (!getStoplichtStatus(0)) {
        exit_stopLicht();
        verkeersState = DodeTijd;
        entry_dodeTijd();
      }
      break;
    case STOPLICHTTWEE:
      if (!getStoplichtStatus(1)) {
        exit_stopLicht();
        verkeersState = DodeTijd;
        entry_dodeTijd();
      }
      break;
    case VEKEERSLAGBOOM:
      if (getslagboom()) {
        exit_slagboom();
        verkeersState = DodeTijd;
        entry_dodeTijd();
      }
      break;
    case QUEUE:
      do_queue();
      if (getqueue == 1) {
        //stoplicht 1
        exit_queue();
        verkeersState = STOPLICHTEEN;
        entry_lichteen();
        break;
      }
      if (getqueue == 2) {
        //stoplicht 2
        exit_queue();
        verkeersState = STOPLICHTTWEE;
        entry_lichttwee();
        break;
      }
      if (getqueue == 3) {
        exit_queue();
        verkeersState = VEKEERSLAGBOOM;
        entry_slagboom();
        break;
      }
      break;
    case NACHT:
      do_nacht();
      if (getDagStand()) {
        exit_nacht();
        verkeersState = START;
        enter_start();
      }
      break;
  }

}

void entry_dodeTijd() {
  previousMillis = currentMillis;
}
void exit_dodetijd() {
  previousMillis = currentMillis;
}
void exit_Start() {
//  ledControlTurnAllOff();
  }
void enter_start() {
//  ledControlTurnAllOn();
}

void exit_stopLicht() {
  getAndRemoveFirstFromQueue();
}
void entry_lichteen() {
  startStopLicht(0);
}

void entry_lichttwee() {
  startStopLicht(1);
}
void exit_slagboom() {
  getAndRemoveFirstFromQueue();
}
void entry_slagboom() {
  startSlagboom();
}
void enter_queue() {}
void exit_queue() {}
void exit_nacht() {}
void do_queue() {
  getqueue = aanDeBeurt();
}
void do_nacht() {
  startSlagboom();
}






//test voor button input
void test() {
  for (int i = 0; i < 3; i++) {
    if (getButton(i)) {
      ledControlTurnOn(i);
    } else {
      ledControlTurnOff(i);
    }
  }
}

//code voor controleren van queue
void printQueue() {
  if (currentMillis - previousMillisQ >= 1000) {
    previousMillisQ = currentMillis;
    Serial.println("====");
    Serial.println("");
    Serial.print(aanDeBeurt());
    for (int i = 0; i < 4; i++) {
      Serial.print(getQueue(i));
      Serial.println("");
      Serial.print(getButton(i));

    }
    Serial.println("");
  }

}
