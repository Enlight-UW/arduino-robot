#include <AccelStepper.h>

// step1 is the left motor and step2 is the right
AccelStepper step1(2, 3, 4, 5);
AccelStepper step2(6, 7, 8, 9);

String input;
char command;

void setup() {
  // put your setup code here, to run once:
  step1.setSpeed(500.0);
  step2.setSpeed(500.0);
  
  Serial.begin(9600);
}

void loop() {
  // read incoming serial string
  while(Serial.available() > 0){
    input = Serial.readString();
  }

  // parsing commands and running motors
  for(int i = 0; i < input.length(); i++){
    command = input.charAt(i);

    /* 
     *  set the desired movements for each motor
     *  (these are a little weird since the motors 
     *  face different directions)
     */
    switch(command){
      case 'w':
        step1.move(1000);
        step2.move(-1000);
        break;
      case 'a':
        step1.move(-1000);
        step2.move(-1000);
        break;
      case 'd':
        step1.move(1000);
        step2.move(1000);
        break;
      case 's':
        step1.move(-1000);
        step2.move(1000);
        break;
      default:
        break;
    }
    
    // after setting the desired location run both motors accordingly
    
    // (I'm not sure if this code is necessary so I'm leaving it commented)
    //step1.run();
    //step2.run();
    
    while(step1.distanceToGo()>0 || step2.distanceToGo()>0){
      step1.run();
      step2.run();
    }
  }
  
}
