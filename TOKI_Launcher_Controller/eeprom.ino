//config data process

//recommend, You change this parameters when release.
const int ADDRES_OFFSET = 5;
const byte ROM_SUMCODE = 0xD2;

void checkRom() { //ROM内の処理的な何か　いじったことないわからん
  if (EEPROM.read(ADDRES_OFFSET) != ROM_SUMCODE) {
#ifdef DEBUG_SW1
    Serial.println("Invalid EEPROM checksum. Load default.");
#endif
  } else {
    loadRom();
#ifdef DEBUG_SW1
    Serial.println("Load from EEPROM succeed.");
#endif
  }
}

//rom -> value(ALL)
//hack:
void loadRom() {
  EEPROM.get(ADDRES_OFFSET + 1, value);

  int addres = ADDRES_OFFSET + 1 + sizeof(value);
  EEPROM.get(addres, select);
}

//write to rom
void writeRom() {
  EEPROM.update(ADDRES_OFFSET, ROM_SUMCODE);
  EEPROM.put(ADDRES_OFFSET + 1, value);
}

//todo: 関数名
//hack:
void writeSelectRom() {
  int addres = ADDRES_OFFSET + 1 + sizeof(value);
  EEPROM.put(addres, select);
}
