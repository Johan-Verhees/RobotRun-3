#include "line.h"
#include <Pololu3piPlus32U4.h>
#include <Arduino.h>
using namespace Pololu3piPlus32U4;
extern LineSensors lineSensors;
extern Motors motors;
extern Buzzer buzzer;

extern ButtonC buttonC;

uint16_t sensorValues[5];
bool useEmitters = true;

uint16_t getSensorValue(int index) {
    return sensorValues[index];
}

const int baseMotorSpeed = 100;  // how fast the motor may spin

void ReadIR() {
  static uint16_t lastSampleTime = 0;

  if ((uint16_t)(millis() - lastSampleTime) >= 10)
  {
    lastSampleTime = millis();

    lineSensors.read(sensorValues, useEmitters ? LineSensorsReadMode::On : LineSensorsReadMode::Off);

    char buffer[80];
    sprintf(buffer, "%4d %4d %4d %4d %4d %c\n",
      sensorValues[0],
      sensorValues[1],
      sensorValues[2],
      sensorValues[3],
      sensorValues[4],
      useEmitters ? 'E' : 'e'
    );
  //  Serial.print(buffer);
  }

  if (buttonC.getSingleDebouncedPress())
  {
    useEmitters = !useEmitters;
    Serial.println(useEmitters);
  }
}

int prevError = 0;

void trackStraight(){
  
      // PID:

    float Kp = 8; // constant for P
    float Kd = 4; // constant for D

    int error = (int)sensorValues[3] - (int)sensorValues[1];

    int derivative = error - prevError;

    int correction = Kp * error + Kd * derivative;

    prevError = error;


  int leftSpeed  = baseMotorSpeed + correction;
  int rightSpeed = baseMotorSpeed - correction;


  motors.setSpeeds(leftSpeed, rightSpeed);
}


uint8_t checkCorner(){
  bool leftCorner = (sensorValues[0] > 10);
  bool rightCorner = (sensorValues[4] > 10);

  if(rightCorner){
    return 1;
  } else if(leftCorner){
    return 2;
  } else{
    return 0;
  }
}

void reactCorner(int currentCorner){
  /*
  keuze links of rechts
  delay voor draaitijd
  dan door met lijnvolgen
  hier maak je voorkeur
  */

  if(currentCorner == 1){ // should turn right
    motors.setSpeeds(baseMotorSpeed, -baseMotorSpeed/2);
    delay(500);

  } else if(currentCorner == 2){
    motors.setSpeeds(-baseMotorSpeed/2, baseMotorSpeed);
    delay(500);

  }
}



void followLine(){

  ReadIR();
  lineSensors.readCalibrated(sensorValues); // read sensors and store info

    reactCorner(checkCorner());
    trackStraight();

}
