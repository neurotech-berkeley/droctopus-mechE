///////////////////////////////////////////////////////////////////////////////////////////////////////
/* DOC OCK MOTOR SOFTWARE
Sets up motor control by driving stepper motors
with PWM output signals


******TODO*******
- Implement state machine

- Implement motor control
  - code encoder for motor position tracking(count steps over time)
  - wire potentiometer to circuit for speed/position control
      - can use joystick (2 channels for two motor control)
      - or use twist potentiometer
  - Reverse Kinematics? 
      - can derive motor inputs given a desired position
  
- Implement hard stops to motors to prevent arm from exceeding max allowable range of motion

*/
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*
DM332T important specs:
  - 2.5 us min setup time -> max freq of 400,000 Hz
*/

//MOTOR PINS
#define DIR 13 // set direction pin
#define PUL1 26 // Motor 1 PWM
#define PUL2 25 // Motor 2 PWM 

//POT PINS (CHANGE)
#define POT1X 14 
#define POT1Y 15

const int ledChannel_1 = 1; // Motor 1 channel
const int ledChannel_2 = 2; // Motor 2 channel
/*
 *** DEFINE MORE MOTOR PINS AND CHANNELS HERE *** 
*/

// change for different motor response 
int readFreq;
int freq1 = 800;
int freq2 = 300;
// define more frequencies here

// Define timers
hw_timer_t * timer0 = NULL;
portMUX_TYPE timerMux1 = portMUX_INITIALIZER_UNLOCKED;



int state = 1; // state var for switch statement in loop()
int x = 1;

// set pulse per rev values for encoder code
// (look at switches on motor driver and set accordingly)
// calculate rot per sec = freq / ppr and count time to track position
const int ppr1 = 400;
const int ppr2 = 800;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(DIR, OUTPUT); // configure DIR pin as out

  //set up PWM channels
  ledcSetup(ledChannel_1, freq1, 8);
  ledcSetup(ledChannel_2, freq2, 8);
  ledcAttachPin(PUL1, ledChannel_1);
  ledcAttachPin(PUL2, ledChannel_2);

  // Write direction (binary input, drive to either HIGH or LOW)
  digitalWrite(DIR, HIGH);
}

void loop() {

  // this code block simply drives the motors at higher speeds until it reaches a threshold
  // and resets. For testing purposes and reference only
  // check driver soecs to see pulses/rev and change frequencies for finer/coarser step sizes
  /*
  freq = 800; // freq / PPR = rps

  ledcChangeFrequency(ledChannel_1, freq, 8); // use this function to write new frequencies
  ledcChangeFrequency(ledChannel_2, freq, 8);
  
  ledcWrite(ledChannel_1, 50); // 50% duty
  ledcWrite(ledChannel_2, 50);
  
  delay(2000); // 2 sec delay

  
  delay(2000);

  // read and print freq to serial monitor
  // to get 
  readFreq = ledcReadFreq(ledChannel_1);
  Serial.print(readFreq);
  Serial.println(freq);
  */

  // control loop/state machine
  switch (state){
    case 1:
      // DO STUFF
      //motor1on(); // change
      ledcWrite(ledChannel_1, 20);
      printMotorData(ledChannel_1, ppr1, true); // print motor 1 state for debugging
      delay(2000);
      // update <state> if needed
      /*
      if ( x % 5000 == 0){
        state = 2;
      }
      */
      break;
    case 2: 
      // DO STUFF
      motor1off(); // change
      // update <state> if needed
      printMotorData(ledChannel_1, ppr1, false); // print motor 1 state for debugging
      if (x % 5000 == 0){
        state = 1;
      }
      break;
    //include other cases as per state machine
  }

  x = x + 1;

  //printMotorData(ledChannel_1, ppr1, true); // print motor 1 state for debugging

}

//////////////////////////////////////////////////////////////////////////////////
// state/helper functions
//////////////////////////////////////////////////////////////////////////////////
void readPot(){
  //TODO: implement potentiometer polling helper function(set up debounce timer, etc.)
}
void motor1on(){ // turn motor 1 on
  ledcWrite(ledChannel_1, 50);
  ledcChangeFrequency(ledChannel_1, freq1, 8);
}
void motor2on(){ // turn motor 2 on
  ledcChangeFrequency(ledChannel_2, freq2, 8);
  ledcWrite(ledChannel_2, 50);
}
// ... include other motoron() functions
void motor1off(){
  ledcWrite(ledChannel_1, 0); // set to 0% duty cycle
}
void motor2off(){
  ledcWrite(ledChannel_2, 0); 
}
/*
bool CheckForButtonPress(){
  if()
}
*/
void printMotorData(const int ledcChannel, const int ppr, bool on){ // print output of motor for debugging purposes
  readFreq = ledcReadFreq(ledcChannel);
  if (on){ // format ex: "Motor 1 speed: 2 rps"
    Serial.print("Motor ");
    Serial.print(ledcChannel);
    Serial.print(" speed: ");
    Serial.print(readFreq / ppr);
    Serial.println(" rps");
  }
  else{ // format ex: "Motor 1 speed: OFF"
    Serial.print("Motor ");
    Serial.print(ledcChannel);
    Serial.println("speed: OFF");
  }
}
// ... include other motoroff() functions


