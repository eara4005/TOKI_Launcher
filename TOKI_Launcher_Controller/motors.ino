
void shooting(int power) {  //バキューム出力（％）
  digitalWrite(PIN_MOTOR_V1_DIR, HIGH);
  analogWrite(PIN_MOTOR_V1_PWM, power * 255 / 100);
}


//void shot() {
//    myservo.write(value.servo_up);  //ハンマ上げ
//    delay(1000);
//
//    toki_count++;
//    lcd.setCursor(1, 1);
//    lcd.print("ﾊｯｼｬｼﾀ ｶｽﾞ");
//    lcd.setCursor(12, 1);
//    lcd.print(toki_count);
//
//    myservo.write(value.servo_down); //ハンマ下げ
//    delay(1000);
//}

void shot2() {  //New SHOOTING Program
  static int state = 0;
  static unsigned long lasttime;

  switch (state) {
    case 0:
      if (ps2x.ButtonPressed(PSB_R2)) {
        myservo.write(value.servo_up);  //ハンマ上げ
        lasttime = millis();
        state++;
      }
      break;

    case 1:
      if (millis() - lasttime >= 1000) {
        toki_count++;
        lcd.setCursor(1, 1);
        lcd.print("ﾄﾘｶﾞﾋｲﾀｶｽﾞ");
        lcd.setCursor(12, 1);
        lcd.print(toki_count);

        myservo.write(value.servo_down); //ハンマ下げ

        lasttime = millis();
        state++;
      }
      break;

    case 2:
      if (millis() - lasttime >= 1000) {
        state = 0;
      }
      break;
  }
}
