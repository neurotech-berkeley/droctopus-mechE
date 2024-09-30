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
  //myStep2.setMaxSpeed(200);
  //myStep2.setAcceleration(50);
  //myStep2.moveTo(100000); 
  // myStep2.moveTo(0); 

  // parameters for the linear motor
   myStep.setMinPulseWidth(15);
   myStep.setSpeed(900);
   myStep.setAcceleration(500);
   myStep.moveTo(10000); 
   //Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  myStep.runSpeed();
  //Serial.print("Is Running: " + myStep.isRunning());
  //Serial.print(" Speed: ");
  //Serial.print(myStep.speed());
  //Serial.print(" cur Pos: ");
  //Serial.println(myStep.currentPosition());

}
