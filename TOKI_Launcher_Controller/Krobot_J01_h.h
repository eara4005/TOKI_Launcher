//%%%Kadai robot 2019%%%///
//header file for hardware

//last update: 2019/06/06
//version: beta
//author: shingo takesawa
//      : (ほかに編集者がいればここに書く)

#ifndef Krobot_J01_h_h
#define Krobot_J01_h_h

//---define pins

//LCD
#define PIN_LCD_RS 48
#define PIN_LCD_RW 43
#define PIN_LCD_EN 42
#define PIN_LCD_D4 41
#define PIN_LCD_D5 40
#define PIN_LCD_D6 39
#define PIN_LCD_D7 38

//user switch
#define PIN_SW1 53
#define PIN_SW2 52
#define PIN_SW3 51
#define PIN_SW4 50
#define PIN_SW5 49

//servo
#define PIN_SERVO 8

//sensor pin
#define PIN_SENSOR_W A12 //壁用
#define PIN_SENSOR_L A0  //光用

//battery sens pin
const int PIN_BAT_COM = A13;
const int PIN_BAT_M0 = A14;
const int PIN_BAT_M1 = A15;

//controller(PS2)
const int PIN_CTL_CLK = 34;
const int PIN_CTL_CMD = 35;
const int PIN_CTL_ATT = 37;
const int PIN_CTL_DAT = 36;

//buzzer
const int PIN_BZ = 47;

//motor pins define
const int PIN_MOTOR_V1_DIR = 29; //バキュームモータ
const int PIN_MOTOR_V1_PWM = 7;

#endif  //end of KROBOT_R01_h_h
