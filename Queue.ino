const int LEEG = 0;
const int STOPLICHT_1 = 1;
const int STOPLICHT_2 = 2;
const int SLAGBOOM = 3;
int queue[] = {0, 0, 0, 0};
int queueLijst[] = {LEEG, STOPLICHT_1, STOPLICHT_2, SLAGBOOM};
int queueLenght = sizeof(queue) / sizeof(int);
int queueLijstLength = sizeof(queueLijst) / sizeof(int);

void loopqueue() {
  if (getButton(0)) {
    queueStopLicht1();
  }
  if (getButton(1)) {
    queueStopLicht2();
  }
  if (getButton(2)) {
    queueSlagBoom();
  }

}



void queueStopLicht1() {
  addToQueue(STOPLICHT_1);
}
void queueStopLicht2() {
  addToQueue(STOPLICHT_2);
}
void queueSlagBoom() {
  addToQueue(SLAGBOOM);
}



//klaar
int getAndRemoveFirstFromQueue() {
  int terug = aanDeBeurt();
  verwijdereerste();
  return terug;
}

//klaar
boolean queueCheck(int x) {
  for (int i = 0; i < getQueueLencht(); i++) {
    if (queue[i] == x) {
      return true;
    }
  }
  return false;
}

//klaar
void addToQueue(int x) {
//  Serial.println("addToQueu");
  if (!queueCheck(x)) {
//    Serial.println("queuecheck");
//    x = constrain(x , queueLijst[0], queueLijst[queueLijstLength]);
    for (int i = 0; i < getQueueLencht(); i++) {
//      Serial.println("for_loop");
      if (queue[i] == LEEG) {
//        Serial.println("isleeg");
        queue[i] = x;
        return;
      }
    }
  }
}


//klaar
int aanDeBeurt() {
  return queue[0];
}

//klaar
void verwijdereerste() {
  for (int i = 0; i < getQueueLencht() - 1; i++) {
    queue[i] = queue[i + 1];
  }
  queue[getQueueLencht() - 1] = LEEG;
}

//klaar
int getQueueLencht() {
  return queueLenght;
}

int getQueue(int i) {
  return queue[i];

}
