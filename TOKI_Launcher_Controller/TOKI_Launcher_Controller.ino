//2019年　課題ロボット　フリスビー発射機構プログラム

//code name: TOKI Launcher LCD

//last update: 2019/07/23
//author: S.Takesawa

//board type: Arduino Mega
//CPU type: ATmega2560

//---description:
//トキ射出台の制御プログラムです。
//自律用プログラムをフリスビー発射機用に最適化したものです。
//また　まさむねくんの力を借りました。

//--update
//ハンマ（サーボ）用の関数を追加
//打ったフリスビーをカウントするUIの処理を追加
//シリアルモニタでデバッグをとれるように変更
/***************************************************/

//include header file
#include "Krobot_J01_h.h"
#include "Krobot_J01_s.h"

//switch用関数
int mode_run = 0;

//コートの選択用変数
byte select = 0x0F;

//カウンタ
int toki_count = 0;

//version string
const char VERSION[4] = "TOKI";

//low battery voltage threshold
const float BAT_COM_LOW = 6.2;
const float BAT_MOTOR_LOW = 3.4 * 3; //10.2V

struct romdata {
  int launcherRange;
  int servo_up;
  int servo_down;
} value = {
  100,
  0, 0
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.kanaOn(); //lcdのカタカナ表示を有効に
  delay(50);
  //initialize
  initPin();
  initLib();
  if (!digitalRead(PIN_SW5)) { //起動時にボタン5が押されていた場合
    Serial.println("Go to Setup");
    mode_run = 100; //設定画面に飛ばす
  }
  bootSplash(); //起動時処理
  checkRom();//ROMの確認

  myservo.write(value.servo_down); //サーボを規定値まで
}

void loop() {
  // put your main code here, to run repeatedly:
  ps2x.read_gamepad();
  switch (mode_run) {
    case 0:
      if (!digitalRead(PIN_SW5) || ps2x.Button(PSB_GREEN)) { //ボタン５を押したら
        Serial.println("GREEN Pressed");
        Serial.println("Reset to Servo");
        myservo.write(value.servo_up); //サーボを規定値まで
        delay(50);
      }
      if (ps2x.Button(PSB_PINK)) {
        mode_run = 1;
      }

    case 100:
      menu(mode_run == 0);  //設定画面に飛ばす
      break;

    //---
    case 1: //動作実行画面
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("ﾄﾞｳｻ ｼﾞｯｺｳﾁｭｳ");
      Serial.println("This Promram Works!");
      mode_run++;
      break;

    case 2://動作の処理
      //発射用モータを起動
      shooting(value.launcherRange);
      if (ps2x.ButtonPressed(PSB_R2)) {
        Serial.println("R2 pressed:SHOOT!");
        // shot();
      }
      else if (ps2x.ButtonPressed(PSB_BLUE)) {
        Serial.println("CROSS pressed:STOP");
        mode_run = 3;
      }
      shot2(); //動作用プログラム
      break;

    case 3://動作停止の処理
      delay(500);
      lcd.clear();
      lcd.print("ﾄﾞｳｻ ｼｭｳﾘｮｳ");
      Serial.println("This Program Stops!");
      delay(500);
      toki_count = 0;
      shooting(0); //発射用モータを止める
      mode_run = 0;
      break;
  }
  delay(16);
}

/****************************************************/
void initPin() { //ピン定義
  //switch pin
  pinMode(PIN_SW1, INPUT_PULLUP);
  pinMode(PIN_SW2, INPUT_PULLUP);
  pinMode(PIN_SW3, INPUT_PULLUP);
  pinMode(PIN_SW4, INPUT_PULLUP);
  pinMode(PIN_SW5, INPUT_PULLUP);
  //motor pin
  pinMode(PIN_MOTOR_V1_DIR, OUTPUT);
}

void initLib() {  //各ライブラリの定義まとめ
  //serial port
  Serial.begin(115200); //[bps]
  //LCD
  lcd.begin(16, 2);
  //servo
  myservo.attach(PIN_SERVO);
  //controller
  ps2x.config_gamepad(PIN_CTL_CLK, PIN_CTL_CMD, PIN_CTL_ATT, PIN_CTL_DAT, true, true); //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
}

/********************************************************/
int search_SW() { //選択スイッチを読み込む
  for (int i = 3; i >= 0; i--) {
    if (bitRead(select, i)) {
      return i;
    }
  }
  return 0;
}

boolean SW_read(int num) {  //選択スイッチの論理を読み出す
  num = constrain(num, 0, 3); //変数:num 最小値:0 最大値:3
  return bitRead(select, num);
}
