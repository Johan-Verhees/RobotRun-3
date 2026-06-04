#include <Arduino.h>
#include <menu.h>
#include <line.h>
#include <motors.h>
#include <line.h>
#include <Pololu3piPlus32U4.h>
#include <Pololu3piPlus32U4LineSensors.h>

bool go = 0;

using namespace Pololu3piPlus32U4;
  LineSensors lineSensors;
  Buzzer buzzer;
  extern ButtonB buttonB;
  extern Motors motors;


void setup() {
  Serial.begin(9600);
  InitMenuSystem();
  lineSensors.calibrate();
  delay(1000);
  buzzer.play("c4r8");
}


void loop() {
//   if(buttonB.getSingleDebouncedPress()){
//   buzzer.play("c4r8");
// go = !go;
//   }
//   while (go == 1){
      followLine();
  // }

  // while (go == 0){
  //   motors.setSpeeds(0, 0);
  // }
}
