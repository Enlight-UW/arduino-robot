// This Arduino example demonstrates bidirectional operation of a
// 28BYJ-48, using a ULN2003 interface board to drive the stepper.
// The 28BYJ-48 motor is a 4-phase, 8-beat motor, geared down by
// a factor of 68. One bipolar winding is on motor pins 1 & 3 and
// the other on motor pins 2 & 4. The step angle is 5.625/64 and the
// operating Frequency is 100pps. Current draw is 92mA.
////////////////////////////////////////////////

// NOTE EVERYTHING MIGHT BE BACKWARD
   
//declare variables for the motor pins
int motorPinsR[4] = {2, 3, 4, 5};    // Blue   - 28BYJ48 pin 1
int motorPinsL[4] = {6, 7, 8, 9};    // Pink   - 28BYJ48 pin 2
//int motorPin3 = 4;    // Yellow - 28BYJ48 pin 3
//int motorPin4 = 5;    // Orange - 28BYJ48 pin 4
                        // Red    - 28BYJ48 pin 5 (VCC)

int motorSpeed = 1200;  //variable to set stepper speed
int count = 0;          // count of steps made
int countperrev = 512; // number of steps per full revolution
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};
float rotationsPerBlock = 1; //FIXME DO MATH
float rotationsPerTurn = 0.4; // FIXME MATH DO IT CIRCUMFERENCE AND STUFF
String input;
char command;

//////////////////////////////////////////////////////////////////////////////
void setup() {
  //declare the motor pins as outputs

  pinMode(motorPinsL[0], OUTPUT);
  pinMode(motorPinsL[1], OUTPUT);
  pinMode(motorPinsL[2], OUTPUT);
  pinMode(motorPinsL[3], OUTPUT);
  pinMode(motorPinsR[0], OUTPUT);
  pinMode(motorPinsR[1], OUTPUT);
  pinMode(motorPinsR[2], OUTPUT);
  pinMode(motorPinsR[3], OUTPUT);
  Serial.begin(9600);
}

//////////////////////////////////////////////////////////////////////////////
void loop(){
  // read incoming serial string
  while(Serial.available() > 0){
    input = Serial.readString();
  }

  // parsing commands and running motors
  for(int i = 0; i < input.length(); i++){
    command = input.charAt(i);
     switch(command){
      case 'w':
        Serial.println("W happened");
        forward();
        //step2.move(-10000);
        break;
      case 'a':
      Serial.println("A happened");
        left();
        //step2.move(-10000);
        break;
      case 'd':
      Serial.println("D happened");
        right();
        //step2.move(10000);
        break;
      case 's':
      Serial.println("S happened");
        backward();
        //step2.move(10000);
        break;
      default:
        break;
      }
    }
  input = "";
}
//////////////////////////////////////////////////////////////////////////////
//set pins to ULN2003 high in sequence from 1 to 4
//delay "motorSpeed" between each pin setting (to determine speed)

void forward(){
  count = countperrev * rotationsPerBlock;
  while (count > 0){
    for(int i = 0; i<8; i++){
      setOutputR(i);
      setOutputL(7-i);
      delayMicroseconds(motorSpeed);
    }
    count--;
  }
  
}

void backward(){
  count = countperrev * rotationsPerBlock;
  while (count > 0){
    for(int i = 0; i<8; i++){
      setOutputR(7-i);
      setOutputL(i);
      delayMicroseconds(motorSpeed);
    }
    count--;
  }
}
void left(){
  count = countperrev * rotationsPerTurn;
  while (count > 0){
    for(int i = 0; i<8; i++){
      setOutputR(i);
      setOutputL(i);
      delayMicroseconds(motorSpeed);
    }
    count--;
  }
}
void right(){
  count = countperrev * rotationsPerTurn;
  while (count > 0){
    for(int i = 0; i<8; i++){
      setOutputR(7-i);
      setOutputL(7-i);
      delayMicroseconds(motorSpeed);
    }
    count--;
  }
}

void setOutputL(int out)
{
  digitalWrite(motorPinsL[0], bitRead(lookup[out], 0));
  digitalWrite(motorPinsL[1], bitRead(lookup[out], 1));
  digitalWrite(motorPinsL[2], bitRead(lookup[out], 2));
  digitalWrite(motorPinsL[3], bitRead(lookup[out], 3));
}
void setOutputR(int out)
{
  digitalWrite(motorPinsR[0], bitRead(lookup[out], 0));
  digitalWrite(motorPinsR[1], bitRead(lookup[out], 1));
  digitalWrite(motorPinsR[2], bitRead(lookup[out], 2));
  digitalWrite(motorPinsR[3], bitRead(lookup[out], 3));
}
void anticlockwiseR()
{
  for(int i = 0; i < 8; i++)
  {
    setOutputR(i);
    delayMicroseconds(motorSpeed);
  }
}

void clockwiseR()
{
  for(int i = 7; i >= 0; i--)
  {
    setOutputR(i);
    delayMicroseconds(motorSpeed);
  }
}

