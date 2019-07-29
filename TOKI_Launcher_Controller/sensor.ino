//sensor process

//get battery voltage[V(float)]
float batteryRead(byte pin) {
  float volt = (float)analogRead(pin) / 1023.0 * 20.1515;
  //if (pin == PIN_BAT_COM) volt += 0.7;
  return volt;
}
