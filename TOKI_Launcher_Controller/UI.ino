//user interface (button & LCD) process

int UIpage = 0;
int UIpage2 = 0;

/******************************************************/

void bootSplash() { //起動時の表示(LCD)
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("AYS Autonomous");
  lcd.setCursor(8, 1);
  lcd.print("ver.");
  lcd.print(VERSION);
  delay(300);
}



/**********************************************************/
unsigned long loopcount = 0;  //main loop counter

void menu(int mode) {
  const unsigned int LCD_REFRESHTIME = 500; //LCD refresh rate[ms]
  static unsigned long lasttime = 0;

  //read user actions
  buttonFunc();
  if (millis() - lasttime >= LCD_REFRESHTIME || buttonRead_rep(ID_SW_ALL)) {
    switch (mode) {
      case 0:
        //configure
        usrInput();
        lcdRefresh();
        break;

      case 1:
        //attack select
        atksel();
        break;
    }
    lasttime = millis();
  }

  delay(16);
  loopcount++;
}

/******************************************/

void usrInput() { //ボタンごとの処理
  if (buttonRead_p(ID_SW1)) writeRom();

  if (buttonRead_rep(ID_SW2)) UIpage++;
  if (buttonRead_rep(ID_SW3)) UIpage--;
  UIpage = constloop(UIpage, 0, 3); //ページを増減させたいときにはここをいじる

  switch (UIpage) {
    case 0:
      break;

    //バキュームモータ出力設定画面の設定
    case 1:
      if (buttonRead_rep(ID_SW4)) value.launcherRange++;
      if (buttonRead_rep(ID_SW5)) value.launcherRange--;
      value.launcherRange = constloop(value.launcherRange, 0, 100);
      break;

    //サーボモータ 上げ角出力設定画面の設定
    case 2:
      if (buttonRead_rep(ID_SW4)) value.servo_up++;
      if (buttonRead_rep(ID_SW5)) value.servo_up--;
      value.servo_up = constloop(value.servo_up, 0, 180);
      break;

    //サーボモータ 下げ角出力設定画面の設定
    case 3:
      if (buttonRead_rep(ID_SW4)) value.servo_down++;
      if (buttonRead_rep(ID_SW5)) value.servo_down--;
      value.servo_down = constloop(value.servo_down, 0, 180);
      break;
  }
}

void lcdRefresh() { //読んで字のごとくです
  char out[32];

  lcd.clear();

  switch (UIpage) {
    case 0: //バッテリ確認画面
      Serial.println("BatterySetup");
      lcd.print("ﾊﾞｯﾃﾘ");
      lcd.setCursor(9, 0);
      dtostrf(batteryRead(PIN_BAT_COM), 4, 1, out);   //Arduino電源
      lcd.print("C:"); lcd.print(out); lcd.print("V");
      lcd.setCursor(0, 1);
      dtostrf(batteryRead(PIN_BAT_M0), 4, 1, out);  //足周り用電源
      lcd.print("M1:"); lcd.print(out); lcd.print("V");
      lcd.setCursor(9, 1);
      dtostrf(batteryRead(PIN_BAT_M0), 4, 1, out);  //バキューム用電源
      lcd.print("M2:"); lcd.print(out); lcd.print("V");
      break;

    case 1: //ランチャーの設定
      Serial.println("LauncherSetup");
      lcd.print("ﾗﾝﾁｬｰ ﾂﾖｻ");
      lcd.setCursor(1, 1);
      sprintf(out, "%3d%c", value.launcherRange, '%');
      lcd.print(out);
      break;

    case 2: //サーボ　上げ角度の設定
      Serial.println("Servo-up Setup");
      lcd.print("ｻｰﾎﾞ ｱｹﾞ");
      lcd.setCursor(1, 1);
      sprintf(out, "%3d[deg]", value.servo_up);
      myservo.write(value.servo_up);
      lcd.print(out);
      break;

    case 3://サーボ　下げ角度の設定
      Serial.println("Servo-down Setup");
      lcd.print("ｻｰﾎﾞ ｻｹﾞ");
      lcd.setCursor(1, 1);
      sprintf(out, "%3d[deg]", value.servo_down);
      myservo.write(value.servo_down);
      lcd.print(out);
      break;
  }
}

/*************************************/

void atksel() { //アタックセレクト　ってよみます

  //前回のボタンの状態
  static boolean oldbtn = 0;

  //開始処理
  if (oldbtn && !buttonRead(ID_SW1)) { //ボタンが離されたとき
    writeSelectRom();
    mode_run++;
  }

  if (buttonRead(ID_SW1)) {   //スタートボタンが押されたとき
  }
  oldbtn = buttonRead(ID_SW1);

  for (int i = 0; i < 4; i++) {
    if (buttonRead_p(bit(i + 1))) bitWrite(select, i, !bitRead(select, i));
  }

  lcd.clear();

  //画面表示
  lcd.setCursor(1, 0);
  lcd.print("ﾌﾘｽﾋﾞｰ ﾊｯｼｬﾓｰﾄﾞ");
}
