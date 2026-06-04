#include "motors.h"
#include <Pololu3piPlus32U4.h>
using namespace Pololu3piPlus32U4;

Motors motors;

// speed values
int maxSpeed = 100;
int speed = 100;

void vooruit() {
  motors.setSpeeds(speed, speed);
}

void achteruit() {
  motors.setSpeeds(-speed, -speed);
}

void rechts() {
  motors.setSpeeds(speed/2, -speed/2);
}

void links() {
  motors.setSpeeds(-speed/2, speed/2);
}

void stop() {
  motors.setSpeeds(0, 0);
}

void linksVoor(){
  motors.setSpeeds(speed, maxSpeed);
}

void rechtsVoor() {
  motors.setSpeeds(maxSpeed, speed);
}