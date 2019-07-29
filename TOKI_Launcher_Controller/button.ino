//button process(UI low-layer process)
//debounce & one shot / key repeat

//time parameter
//T1:start T2:freq [flame]
const int KEYREP_T1 = 25;
const int KEYREP_T2 = 4;

byte btnstate = B00000;
byte btnstate_p = B00000;
byte btnstate_prep = B00000;

unsigned long btnprstime[5];

/******************************************************/

//*call at 1 loop
void buttonFunc() {
  static byte oldbtnstate = B00000;
  byte btnstate_rep = B00000;
  
  static byte oldstate = B11111;  //*negative
  static byte state = B11111;   //*negative

  oldstate = state;
  state = digitalRead(PIN_SW1) | digitalRead(PIN_SW2) << 1 | digitalRead(PIN_SW3) << 2 | digitalRead(PIN_SW4) << 3 | digitalRead(PIN_SW5) << 4;

  oldbtnstate = btnstate;

  btnstate |= ~(oldstate | state);  //->on
  btnstate &= ~(oldstate & state);  //->off

  btnstate_p = btnstate & ~oldbtnstate;

  //key repeat
  for (int i = 0; i <= 4; i++) {
    if (btnstate_p & 1 << i) btnprstime[i] = loopcount;  //start keyrep
    if (~btnstate & 1 << i) continue;   //end keyrep
    if (loopcount - btnprstime[i] < KEYREP_T1)  continue;  //skip till KEYREP_T1
    int x = (loopcount - btnprstime[i] - KEYREP_T1) % KEYREP_T2;
    btnstate_rep = btnstate_rep | (x == 0) << i;
  }
  btnstate_prep = btnstate_p | btnstate_rep;
}

//press
boolean buttonRead(byte btnid) {
  return !!(btnstate & btnid);
}
//press one shot
boolean buttonRead_p(byte btnid) {
  return !!(btnstate_p & btnid);
}
//press + key repeat
boolean buttonRead_rep(byte btnid) {
  return !!(btnstate_prep & btnid);
}
