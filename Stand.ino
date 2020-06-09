boolean DagStand = true;

void setupStand() {
  LDRSetup();
}
void loopStand() {
  if (getLDR() > 250) {
    DagStand = false;
  } else {
   DagStand= true;
  }
}
boolean getDagStand() {
  return DagStand;
}
