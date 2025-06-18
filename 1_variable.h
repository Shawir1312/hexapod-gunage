#include <Servo.h>
#include <EEPROMex.h>
#include "Arduino.h"
#include <math.h>
#include <avr/pgmspace.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 Oled(128, 64, &Wire, 4);

#define ledOledPin A0
#define buzzerPin A1
#define btnOledPin A2
#define bat2sSensPin A3
#define bat1sSensPin A4



float voltageReading;
float voltageReading1;
float batVol, batVol1, batPct;

Servo srv_1A; Servo srv_1B; Servo srv_1C;
Servo srv_2A; Servo srv_2B; Servo srv_2C;
Servo srv_3A; Servo srv_3B; Servo srv_3C;
Servo srv_4A; Servo srv_4B; Servo srv_4C;
Servo srv_5A; Servo srv_5B; Servo srv_5C;
Servo srv_6A; Servo srv_6B; Servo srv_6C;
Servo myservoA; Servo myservoB; Servo myservoC;
Servo srv_GR; Servo srv_UP; Servo srv_k;

#define JSD 19//25//19
#define stp 36//47//36
//=========PID VARIABLE
float Kp = 5;
float Ki = 1;
float Kd = 0.1;
//=========PIT STOP VARIABLE
byte startPoint = 0;
byte stopPoint = 99;
byte wallDistance = 10;
byte frontDistance = 15;
int  fireLimit = 300;

//=========RUN VARIABLE
extern int JS;
int addStep = JS + JS - 2;
byte sp = 1;
float left = 1;
float right = 1;

float leftCalibration = 1;
float rightCalibration = 1;

byte langkah = 0;
byte gaitsMode = 3; //GAITS 1. Metachronal, 2. Ripple, 3. Tripod
byte xspd = 15; //max 20
byte spd = 25 - xspd;
//byte spd = 5;


int dly  = 10;
float wide = 0; //max 25
float lift = 15; //max 25

float yAxis = 30;
float xAxis = 70;//Min 60
float zAxis = 5;

//=========Body VARIABLE
float cx = 40; //coxa a1
float fm = 60; //femur a2
float tb = 110;//tibia a3
float Zo = 50;//40

//=======Kinematik===============================
int runAngle[] = {0, 0, 0, 0, 0, 0, 0};
byte cxAngle = 90;
byte fmAngle = 0;
byte tbAngle = 0;

byte cx0 = 0;
byte fm0 = 10;
byte tb0 = 10;

long numberStep = 0;
long jumlahLangkah = 0;

byte testSt = 0;
byte hitungJalan = 0;

//=========CALIBRATION VARIABLE
int calA[] = {0, 0, 0, 0, 0, 0, 0};
int calB[] = {0, 10, 10, 10, 10, 10, 10};
int calC[] = {0, 10, 10, 10, 10, 10, 10};

float Adl1; // untuk mencek Hasil perhitungan

byte batSt = 2;
byte readySt = 0;
byte runSt = 0;
byte direction = 1;
byte directionSt = 0;
long startStep = 0;
long runtStepNumber = 0;

int pos0 = 180;

//======== Trajectory variable
float U1[stp];
float W1[stp];
float U2[stp];
float W2[stp];

//======== Gaits variable
byte s0[95];
byte s1[stp];
byte s6[stp];
byte s2[stp];
byte s5[stp];
byte s4[stp];
byte s3[stp];

float pos_1A = cxAngle + calA[1], pos_1B = fmAngle + calB[1], pos_1C = tbAngle + calC[1];
float pos_2A = cxAngle + calA[2], pos_2B = fmAngle + calB[2], pos_2C = tbAngle + calC[2];
float pos_3A = cxAngle + calA[3], pos_3B = fmAngle + calB[3], pos_3C = tbAngle + calC[3];
float pos_4A = cxAngle + calA[4], pos_4B = fmAngle + calB[4], pos_4C = tbAngle + calC[4];
float pos_5A = cxAngle + calA[5], pos_5B = fmAngle + calB[5], pos_5C = tbAngle + calC[5];
float pos_6A = cxAngle + calA[6], pos_6B = fmAngle + calB[6], pos_6C = tbAngle + calC[6];

float AdL[JSD], BdL[JSD], CdL[JSD], AdR[JSD], BdR[JSD], CdR[JSD];
float AtL[JSD], BtL[JSD], CtL[JSD], AtR[JSD], BtR[JSD], CtR[JSD];
float AbL[JSD], BbL[JSD], CbL[JSD], AbR[JSD], BbR[JSD], CbR[JSD];


float mapFloat(float x, float fromLow, float fromHigh, float toLow, float toHigh) {
  return (x - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}

void printSerial(String S1, String S2, String S3, float dA, float dB, float dC, int s) {
  Serial.print(S1 + "[" + String(s) + "] ");
  Serial.print(dA, 1); Serial.print(" \t");
  Serial.print(S2 + "[" + String(s) + "] ");
  Serial.print(dB, 1); Serial.print(" \t");
  Serial.print(S3 + "[" + String(s) + "] ");
  Serial.print(dC, 1);
  Serial.println();
  if (s == JS) Serial.println();
}

void printSerial_1() {
  Serial.print ("xAxis "); Serial.print(" \t");
  Serial.print (xAxis); Serial.print(" \t");
  Serial.print ("yAxis "); Serial.print(" \t");
  Serial.print (yAxis); Serial.print(" \t");
  Serial.print ("zAxis "); Serial.print(" \t");
  Serial.println (zAxis);
  Serial.print ("delay "); Serial.print(" \t");
  Serial.print (dly); Serial.print(" \t");
  Serial.print ("Speed "); Serial.print(" \t");
  Serial.println (spd);
}
