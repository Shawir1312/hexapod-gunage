//Hexapod_Kinematik_MultiStep_MASTER_H04_03a
//by Siful Jamaan, PhD, 16-07-2021

#include "1_Variable.h"

byte printOut = 0;
int P36 = 6;

byte smothtly = 3; //1, 2, 3, 4
int JS = 18; //6, 12, 18, 24 smoothly
byte calSt = 1;
byte dir = 1;
byte pushSt = 1;//BT
byte btSt = 0;
byte activeSt = 0;
byte clrSt = 0;
byte oledSt = 0;
byte kipasSt = 0;
byte apiSt = 0;
byte buzzerApiSt = 0;
int menuSt = 0;


void setup() {
  Serial.begin(9600);//
  Serial.println();
  Serial.println("Quadruped Robot Program");
  testOledSt();
  //testBTSt();
  //pinMode(buzzerPin, OUTPUT);
  EEPROM_ARR(3); //Untuk menyimpan file eeprom kalibrasi

  if (calSt == 1) {
    gaitsTrajectoryCalculation(smothtly);
    moveToCalculation(dir);
    calSt = 0;
  }
//  setupServo(1);
//  kipasOn();
//  beep1();
//  beep();
  delay(500);
  pushSt = 0;
  Serial.print("yAxis ");
  Serial.println(yAxis);
}

void loop() { // ini untuk mencoba fungsi dari bbrp void
  //oledNavigator();
  //timer();
  //action();
  //Serial.print("btSt ");
  //Serial.println(btSt);
  //delay(500);
  //setServoA(45, 100); // Gripper 100 tutup, 30 buka
  //setServoB(46, 180);  //0 UP  180 Down
  //testServo(47); // kipas
  kalibrasi();
  //bacaApi();
  //ukurJarak();
}



void action() {
  if (langkah < addStep)
    langkah++;
  action_1(langkah);
}

void stanBy() {
  if (directionSt != 1) {
    moveToCalculation(2);
    directionSt = 1;
  }
  if (langkah >= addStep / 2) {
    if (langkah < addStep) {
      langkah++;
      moveTo(langkah);
    }
  } else if (langkah > 1) {
    numberStep -= 1;
    langkah--;
    moveTo(langkah);
  }
}
