//Includes the Arduino Stepper Library
#include <Stepper.h>

int x;

// Stepper settings
// Defines the number of steps per rotation
const int stepsPerRevolution = 1892; //473 steps for 10 v for 1/4 circle
const int twentyPerRevolution = 118;
const int fortyPerRevolution = 236;


#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6

// DC motor
int ena = 10;
int in1 = 11;
int in2 = 12;


// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, IN1, IN2, IN3, IN4);

void setup() {
// python communication
  Serial.begin(115200);
  Serial.setTimeout(1);
  
  // Dc MOTOR
pinMode(ena, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
  
  // Nothing to do (Stepper Library sets pins as outputs)

//PlayerOneTurn();
//PlayerTwoTurn();
//DealerTurn();
//PlayerThreeTurn();
//PlayerFourTurn();
//ResetStartPosition_one();
//ResetStartPosition_two();
//ResetStartPosition_three();
//ResetStartPosition_four();

}


void loop(){
  // python communication 
  while (!Serial.available());
  x = Serial.readString().toInt();
  Serial.print(x);
 Play();
}



void PlayerOneTurn() {
  myStepper.setSpeed(6);
  myStepper.step(twentyPerRevolution);
  delay(500);
  DcMotor();
}


void PlayerTwoTurn() {
  myStepper.setSpeed(6);
  myStepper.step(fortyPerRevolution);
  delay(500);
  DcMotor();
}

void DealerTurn(){
  myStepper.setSpeed(6);
  myStepper.step(twentyPerRevolution);
  delay(500);
  DcMotor();
  
}


void PlayerThreeTurn() {
  myStepper.setSpeed(6);
  myStepper.step(twentyPerRevolution);
  delay(500);
  DcMotor();
}


void PlayerFourTurn() {
  myStepper.setSpeed(6);
  myStepper.step(fortyPerRevolution);
  delay(500);
  DcMotor();
}


void ResetStartPosition_one(){
  myStepper.setSpeed(8);
  myStepper.step(-354);
}
void ResetStartPosition_two(){
  myStepper.setSpeed(8);
  myStepper.step(-473);
}
void ResetStartPosition_three(){
  myStepper.setSpeed(8);
  myStepper.step(-591);
}
void ResetStartPosition_four(){
  myStepper.setSpeed(8);
  myStepper.step(-828);
}




void DcMotor() {
  //DC MOTOR
   //CLOCKWISE MAX SPEED
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(ena, 255);
  delay(200);
   digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  delay(1000);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(ena, 255);
  delay(100);
  //STOP
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  delay(500);
}

void Play(){
if (x == 1){
  PlayerOneTurn();
  PlayerTwoTurn();
  ResetStartPosition_one();
}
if (x == 2){
  PlayerOneTurn();
  PlayerTwoTurn();
  DealerTurn();
  ResetStartPosition_two();
}
if (x == 3){
  PlayerOneTurn();
  PlayerTwoTurn();
  DealerTurn();
  PlayerThreeTurn();
  ResetStartPosition_three();
}
if (x == 4){
  PlayerOneTurn();
  PlayerTwoTurn();
  DealerTurn();
  PlayerThreeTurn();
  PlayerFourTurn();
  ResetStartPosition_four();
}
}
