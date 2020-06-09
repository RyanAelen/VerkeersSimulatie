const int AANTALKNOPPEN = 3;
const int BUTONPIN0 = 13;
const int BUTONPIN1 = 12;
const int BUTONPIN2 = 11;
const int BUTTONARRAY[] = {BUTONPIN0, BUTONPIN1, BUTONPIN2};
const int PRESSED = 0;
const int RELEASED = 1;
const int PRESSED_CHECK = 2;
const int RELEASED_CHECK = 3;
const int TIMMERINTERVAL = 30;
boolean buttons[3];
int button_STATE[AANTALKNOPPEN];

unsigned long currentButtonTimer;
unsigned long previousMillisButtonTimer[AANTALKNOPPEN];
//setup code
void setupBUTTONS() {
  for (int i = 0; i < 3; i ++) {
    pinMode(BUTTONARRAY[i], INPUT);
    buttons[i] = false;
    button_STATE[i] = RELEASED;
  }
}

//loop code
void loopBUTTONS(unsigned long currenttime) {
  currentButtonTimer = currenttime;
  tikButtons();
  buttonsStateMachine();

}
//button getter
boolean getButton(int x) {
  int i = button_STATE[x];
  if (i == PRESSED) {
    return true;
  } else if (i == RELEASED) {
    return false;
  } else if (i == PRESSED_CHECK) {
    return false;
  } else if (i == RELEASED_CHECK) {
    return true;
  } else {
    return false;
  }
}
//state machine code
void buttonsStateMachine() {
  for (int i = 0; i < AANTALKNOPPEN; i++) {
    switch (button_STATE[i]) {
      case PRESSED: /////////////
        //button_up
        if (!buttons[i]) {
//          Serial.println("check realeas_check ");
          //switch to realaesed_check
          button_STATE[i] = RELEASED_CHECK;
          previousMillisButtonTimer[i] = currentButtonTimer;
          break;
        }
        break;
      case RELEASED: /////////////
        //button_down
        if (buttons[i]) {
          //switch to pressed_check
          button_STATE[i] = PRESSED_CHECK;
          previousMillisButtonTimer[i] = currentButtonTimer;
          break;
        }
        break;
      case PRESSED_CHECK: /////////////
        //button_up
        if (!buttons[i]) {
          //switch to relased
          button_STATE[i] = RELEASED;
          break;
        }
        //Timmer 30millis
        if (buttonTimmer(i)) {
          if (buttons[i]) {
            //switch to pressed
            button_STATE[i] = PRESSED;
            break;
          }
        }
        break;
      case RELEASED_CHECK: //////////////
        //button_down
        if (buttons[i]) {
//          Serial.println("check Pressed 1");
          //switch to pressed
          button_STATE[i] = PRESSED;
          break;
          
        }
        //timmer 30millis
        if (!buttonTimmer(i)) {
          if (!buttons[i]) {
//            Serial.println("check Realeased 1");
            //switcht to released
            button_STATE[i] = RELEASED;
            break;
          }
        }
        break;
    }
  }
}

boolean buttonTimmer(int i) {
  if (currentButtonTimer - previousMillisButtonTimer[i] >= TIMMERINTERVAL) {
    previousMillisButtonTimer[i] = currentButtonTimer;
    return true;
  }
  return false;
}
void tikButtons() {
  for (int i = 0; i < AANTALKNOPPEN; i++) {
    buttons[i] = !(digitalRead(BUTTONARRAY[i]));
  }
}
