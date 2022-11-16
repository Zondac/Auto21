//Includes the Arduino Stepper Library
#include <Stepper.h>

int x;
// Stepper settings
// Defines the number of steps per rotation
const int stepsPerRevolution = 1892; //473 steps for 10 v for 1/4 circle
const int twentyPerRevolution = 480;
int currentLocation = 0;

int locationarray[5]  {twentyPerRevolution, twentyPerRevolution*3,twentyPerRevolution*4,twentyPerRevolution*5,twentyPerRevolution*7};

//Stepper motor
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6

// DC motor
int ena = 10;
int in1 = 11;
int in2 = 12;

//Numeric variables
int speed1 = 15;
int speed2 = 30;
int delaytime = 250;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN2 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, IN1, IN2);

void setup() {
// python communication
  Serial.begin(115200);
  Serial.setTimeout(1);
  
  // Dc MOTOR
pinMode(ena, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
}

void loop(){
//   python communication 
 while (!Serial.available());
 x = Serial.readString().toInt();
 
 initialDeal(x+1);

 myStepper.step(-currentLocation);
 currentLocation = 0;
}


void  MoveToPlayer(int player) {
  myStepper.setSpeed(speed1);
  myStepper.step(locationarray[player-1]-currentLocation);
  currentLocation = locationarray[player-1];
}

void DcMotor() {
  //DC MOTOR
   //CLOCKWISE MAX SPEED
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(ena, HIGH);
  delay(95);
   digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  delay(20);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(ena, HIGH);
  delay(50);
  //STOP
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  delay(50);
}

void initialDeal(int playeramount){
  for (size_t y = 0; y < 2; y++)
  {
  
  for (size_t i = 1; i <= playeramount; i++)
    {
      MoveToPlayer(i);
      while(!Serial.available());
      Serial.read();
      DcMotor();
    }
  }
}

