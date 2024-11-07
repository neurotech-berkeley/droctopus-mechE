#include <AccelStepper.h>

// Change driver pins accordingly
// can be any output pins
#define PUL1 23 
#define DIR1 21

#define PUL2 19 
#define DIR2 18

AccelStepper myStep(AccelStepper::DRIVER, PUL1, DIR1); // driver config
AccelStepper myStep2(AccelStepper::DRIVER, PUL2, DIR2); // driver config

void setup() {
  // put your setup code here, to run once:

  // parameters for the linear motor
  myStep2.setMaxSpeed(200);
  myStep2.setAcceleration(10);
  myStep2.moveTo(1000); 
  // myStep2.moveTo(0); 

  // parameters for the linear motor
  // myStep.setMaxSpeed(800);
  // myStep.setAcceleration(100);
  // myStep.moveTo(8000); 
}

void loop() {
  // put your main code here, to run repeatedly:
  myStep.run();

}


// void setup() {}

// void loop() {}
