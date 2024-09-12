#include <AccelStepper.h>

// Change driver pins accordingly
// can be any output pins
#define PUL1 13 
#define DIR 16

AccelStepper myStep(AccelStepper::DRIVER, PUL1, DIR); // driver config

void setup() {
  // put your setup code here, to run once:
  myStep.setMaxSpeed(100);
  myStep.setAcceleration(25);
  myStep.moveTo(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  myStep.run();

}
