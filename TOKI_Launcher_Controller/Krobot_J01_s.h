//%%%Kadai Rotot 2019%%%//
//header file for software

//last update: 2019/06/06
//version: beta
//author: shingo takesawa
//      : (ほかに編集者がいればここに書く)

#ifndef Krobot_J01_s_h
#define Krobot_J01_s_h

#include "Krobot_J01_s.h"

//debug switch
#define DEBUG_SW1   //serial console
#define DEBUG_SW2   //beep

//---include libraries
#include <stdio.h>
#include <math.h>
#include <PS2X_lib.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <KanaLiquidCrystal.h>
#include <Servo.h>

//---class define for library
KanaLiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_RW, PIN_LCD_EN, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);
Servo myservo;
PS2X ps2x;

//---button id
#define ID_SW1 0x01
#define ID_SW2 0x02
#define ID_SW3 0x04
#define ID_SW4 0x08
#define ID_SW5 0x10
#define ID_SW_ALL 0x1F

//---functions
//text process
#define TF(x) ((x)==false?'F':'T')
#define HL(x) ((x)==LOW?'L':'H')
//number process
#define constloop(amt,low,high) ((amt)<(low)?(high):((amt)>(high)?(low):(amt)))
#define sgn(x) ((x)<0?0:1)  //signature

#endif  //end of KROBOT_H30_s_01_h
