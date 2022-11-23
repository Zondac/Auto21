#include <Stepper.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int inputint;
String inputintr;
String inputraw;
char output;
bool readysignal;
char inputchar;
// Stepper settings
// Defines the number of steps per rotation
const int stepsPerRevolution = 1892; // 473 steps for 10 v for 1/4 circle
const int twentyPerRevolution = 480;
int currentLocation = 0;

int locationarray[5]{twentyPerRevolution, twentyPerRevolution * 3, twentyPerRevolution * 4, twentyPerRevolution * 5, twentyPerRevolution * 7};

struct player{
  int btna;
  int btnb;
  int btnc;
};

player player1 = {22, 23, 24};
player player2 = {25, 26, 27};
player player3 = {28, 29, 30};
player player4 = {31, 32, 33};

LiquidCrystal_I2C lcd[4] = {
    LiquidCrystal_I2C(0x25, 16, 2),   //Black,  player 1
    LiquidCrystal_I2C(0x27, 16, 2),   //Gray,   player 2   
    LiquidCrystal_I2C(0x3F, 16, 2),   //Yellow, player 3
    LiquidCrystal_I2C(0x26, 16, 2)};  //Red,    player 4

// Stepper motor
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6

int c1s = 50;
int c2s = 51;
int c3s = 52;
int c4s = 53;


// DC motor
int ena = 10;
int in1 = 11;
int in2 = 12;

// Numeric variables
int speed1 = 15;
int speed2 = 30;
int delaytime = 250;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN2 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, IN1, IN2);

void setup()
{ 
  // python communication
  Serial.begin(115200);
  Serial.setTimeout(1);

  // Dc MOTOR
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(c1s, INPUT);
  pinMode(c2s, INPUT);
  pinMode(c3s, INPUT);
  pinMode(c4s, INPUT);

  pinMode(player1.btna, INPUT_PULLUP);
  pinMode(player1.btnb, INPUT_PULLUP);
  pinMode(player1.btnc, INPUT_PULLUP);
  pinMode(player2.btna, INPUT_PULLUP);
  pinMode(player2.btnb, INPUT_PULLUP);
  pinMode(player2.btnc, INPUT_PULLUP);
  pinMode(player3.btna, INPUT_PULLUP);
  pinMode(player3.btnb, INPUT_PULLUP);
  pinMode(player3.btnc, INPUT_PULLUP);
  pinMode(player4.btna, INPUT_PULLUP);
  pinMode(player4.btnb, INPUT_PULLUP);
  pinMode(player4.btnc, INPUT_PULLUP);
  
  for (size_t i = 0; i < 4; i++)
  { 
    lcd[i].init();
    lcd[i].begin(16, 2);
    lcd[i].backlight();
    lcd[i].clear();
    lcd[i].setCursor(0, 0);
    lcd[i].print("Chips:");
    lcd[i].setCursor(0, 1);
    lcd[i].noCursor();
    lcd[i].print("                ");
    lcd[i].setCursor(0, 1);
    lcd[i].print(2000000);
    lcd[i].setCursor(0, 1);
  }
}

void loop()
{
  while (Serial.available() > 0){
    inputraw = Serial.readString();
    inputchar = inputraw.charAt(0);
    inputraw.remove(0,1);
    inputint = inputraw.toInt();


    switch (inputchar)
    {
    case 'd':
      output = getPlayerInput(&player1);
      break;
    
    case 'e':
      output = getPlayerInput(&player2);
      break;
    
    case 'f':
      output = getPlayerInput(&player3);
      break;
    
    case 'g':
      output = getPlayerInput(&player4);
      break;
    
    case 'p':
      DcMotor();
      break;
    
    case 'h':
      resetLocation();
      break;
    
    case 's':
      resetLocation();
      blackjackBegin();
      break;
    
    case 'i':
      lcd[0].print("                ");
      lcd[0].setCursor(0, 1);
      lcd[0].print(inputint);
      lcd[0].setCursor(0, 1);
      break;
    
    case 'j':
      lcd[1].print("                ");
      lcd[1].setCursor(0, 1);
      lcd[1].print(inputint);
      lcd[1].setCursor(0, 1);
      break;

    case 'k':
      lcd[2].print("                ");
      lcd[2].setCursor(0, 1);
      lcd[2].print(inputint);
      lcd[2].setCursor(0, 1);
      break;

    case 'l':
      lcd[3].print("                ");
      lcd[3].setCursor(0, 1);
      lcd[3].print(inputint);
      lcd[3].setCursor(0, 1);
      break;

      case 'm':
      Serial.print(playerAmount());
      break;
      
    default:
      break;
    }

    Serial.print(output);
  }
}

void MoveToPlayer(int player)
{
  myStepper.setSpeed(speed1);
  myStepper.step(locationarray[player - 1] - currentLocation);
  currentLocation = locationarray[player - 1];
}

void DcMotor()
{
  // DC MOTOR
  // CLOCKWISE MAX SPEED
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(ena, HIGH);
  delay(95);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(20);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(ena, HIGH);
  delay(50);
  // STOP
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(50);
}

void initialDeal(int playeramount)
{
  for (size_t y = 0; y < 2; y++)
  {

    for (size_t i = 1; i <= playeramount; i++)
    {
      MoveToPlayer(i);
      while (!Serial.available())
        ;
      Serial.read();
      DcMotor();
    }
  }
}

void resetLocation()
{
  myStepper.step(-currentLocation);
  currentLocation = 0;
}

void blackjackBegin()
{
  while (!Serial.available())
    ;
  inputraw = Serial.readString();
  inputint = inputraw.toInt();
  initialDeal(playerAmount()+1);
  Serial.read();
}

int playerAmount(){
  int var = 4;
  var -= digitalRead(c1s);
  var -= digitalRead(c2s);
  var -= digitalRead(c3s);
  var -= digitalRead(c4s);
  return var;
}

char getPlayerInput(player* reqplayer){
  while (true){
  if(!digitalRead(reqplayer->btna)){
    return 'a';
  }
  else if (!digitalRead(reqplayer->btnb))
  {
    return 'b';
  }
  else if (!digitalRead(reqplayer->btnc)){
    return 'c';
  }
  }

}