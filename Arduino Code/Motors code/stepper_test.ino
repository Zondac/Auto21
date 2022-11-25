#include <Stepper.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int inputint;
String inputintr;
String inputraw;
char output;
bool readysignal;
char inputchar;
int currentplayer = 0;
int players = 1;
char selectionchar;
bool doneselecting = false;
bool doneselecting2 = false;

// Stepper settings
// Defines the number of steps per rotation
const int stepsPerRevolution = 1892; // 473 steps for 10 v for 1/4 circle
const int twentyPerRevolution = 480;

int currentLocation = 0;

int locationarray[5]{twentyPerRevolution*7, twentyPerRevolution * 5, twentyPerRevolution * 4, twentyPerRevolution * 3, twentyPerRevolution};

struct player{
  char ID;
  int chips;
  int btna;
  int btnb;
  int btnc;
  LiquidCrystal_I2C playerscreen;
};

LiquidCrystal_I2C lcd[4] = {
    LiquidCrystal_I2C(0x25, 16, 2),   //Black,  player 1
    LiquidCrystal_I2C(0x27, 16, 2),   //Gray,   player 2   
    LiquidCrystal_I2C(0x3F, 16, 2),   //Yellow, player 3
    LiquidCrystal_I2C(0x26, 16, 2)};  //Red,    player 4

player player1 = {'1' ,20000, 22, 23, 24, lcd[0]};
player player2 = {'2' ,20000, 25, 26, 27, lcd[1]};
player player3 = {'3' ,20000, 28, 29, 30, lcd[2]};
player player4 = {'4' ,20000, 31, 32, 33, lcd[3]};

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
int speed2 = 35;
int delaytime = 200;

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
    lcd[i].noCursor();
    setChips(lcd[i], 20000);
  }
  Serial.println('r');
}
char playerID = 0;
bool screenwritten = false;
void loop()
{
  
  if(inputchar == 'd' ||inputchar == 'e' ||inputchar == 'f' ||inputchar == 'g'){
    playerID = inputchar;
    screenwritten = false;
    inputchar = 0;
  }
  
  if (playerID == 'd'){
    if (!screenwritten)
    {
      screenWrite(player1.playerscreen, "Hit    DD  Stand", " A     B     C  ");
      screenwritten = true;
    }

    sendPlayerInput(player1); 
    }

  if (playerID == 'e'){
    if (!screenwritten)
    {
      screenWrite(player2.playerscreen, "Hit    DD  Stand", " A     B     C  ");
      screenwritten = true;
    }
    sendPlayerInput(player2); 
    }

  if (playerID == 'f'){
    if (!screenwritten)
    {
      screenWrite(player3.playerscreen, "Hit    DD  Stand", " A     B     C  ");
      screenwritten = true;
    }
    sendPlayerInput(player3); 
    }
  if (playerID == 'g'){
    if (!screenwritten)
    {
      screenWrite(player4.playerscreen, "Hit    DD  Stand", " A      B    C  ");
      screenwritten = true;
    }
    sendPlayerInput(player4); 
    }

  while (Serial.available() > 0){
    inputraw = Serial.readString();
    inputchar = inputraw.charAt(0);
    inputraw.remove(0,1);
    inputint = inputraw.toInt();


    switch (inputchar)
    {
    case 'p':
      DcMotor();
      break;
    
    case 'm':
      MoveToPlayer(inputint);
      Serial.println('v');
      break;
    case 's':
      resetLocation();
      Serial.println('v');
      break;
    
    case 'i':
      setChips(lcd[0], inputint);
      player1.chips = inputint;
      Serial.println('v');
      break;
    
    case 'j':
      setChips(lcd[1], inputint);
      player2.chips = inputint;
      Serial.println('v');
      break;

    case 'k':
      setChips(lcd[2], inputint);
      player3.chips = inputint;
      Serial.println('v');
      break;

    case 'l':
      setChips(lcd[3], inputint);
      player4.chips = inputint;
      Serial.println('v');
      break;

    case 'q':

      resetLocation();
      doneselecting2 = false;
      screenWrite(player1.playerscreen, "Another round?  ", "Yes           No");
      while(!doneselecting2){
      output = getPlayerInput(&player1);
      if (output != 'b') doneselecting2 = true;
      }
      setChips(lcd[0], player1.chips);
      break;

    case 'x':

      doneselecting = false;
      //delay(5000);
      lcd[0].setCursor(0,1);
      lcd[0].setBacklight(true);
      lcd[0].printstr("                ");
      while(!doneselecting){
        lcd[0].setCursor(0,0);
        lcd[0].printstr("Select players: ");
        lcd[0].setCursor(0,1);
        lcd[0].print(players);
        selectionchar = getPlayerInput(&player1);
        switch (selectionchar)
        {
        case 'a':
          if(players == 1){
            players = 4;
          }
          else{
            players--;
          }
          lcd[0].setCursor(0,1);
          lcd[0].print(players);
          lcd[0].setCursor(0,1);
          delay(300);
          
          break;

        case 'b':
          doneselecting = true;
          setChips(lcd[0], player1.chips);
          break;
        
        case 'c':

          if(players == 4){
            players = 1;
          }
          else{
            players++;
          }
          lcd[0].setCursor(0,1);
          lcd[0].print(players);
          lcd[0].setCursor(0,1);
          delay(300);
          break;

        default:
          break;
        }

      }

      Serial.println(players);
      break;

    default:
      break;
    }
    Serial.println(output);
    output = 0;
  }
}


void MoveToPlayer(int player)
{
  myStepper.setSpeed(speed2);
  myStepper.step(locationarray[player] - currentLocation);
  currentLocation = locationarray[player];
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
  Serial.println("Card dealt");
}

void initialDeal(int playeramount)
{
  for (size_t y = 0; y < 2; y++)
  {

    for (size_t i = 1; i <= playeramount; i++)
    {
      MoveToPlayer(i);
      while (!Serial.available()){};
      Serial.read();
      DcMotor();
      currentplayer = i;
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
  Serial.read();
  while (!Serial.available()){};
  inputraw = Serial.readString();
  inputint = inputraw.toInt();
  initialDeal(players+1);
  Serial.read();
  Serial.println('r');
}

int playerAmount(){
  int var = 4;
  var -= digitalRead(c1s);
  var -= digitalRead(c2s);
  var -= digitalRead(c3s);
  var -= digitalRead(c4s);
  return var;
}

void sendPlayerInput(player reqplayer){
  
  if(!digitalRead(reqplayer.btna)){
    Serial.println('a');
    setChips(reqplayer.playerscreen, reqplayer.chips);
    playerID = 0;
  }
  else if (!digitalRead(reqplayer.btnb))
  {
    Serial.println('b');
    setChips(reqplayer.playerscreen, reqplayer.chips);
    playerID = 0;
  }
  else if (!digitalRead(reqplayer.btnc)){
    Serial.println('c');
    setChips(reqplayer.playerscreen, reqplayer.chips);
    playerID = 0;
  }
  
}

char getPlayerInput(player* reqplayer){
  while(true){
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

void setChips(LiquidCrystal_I2C screen,int x){
    screen.begin(16,2);
    screen.setCursor(0, 0);
    screen.backlight();
    screen.print("Chips:          ");
    screen.setCursor(0, 1);
    screen.print(x);

}

void screenWrite(LiquidCrystal_I2C screen, String row1, String row2){
    screen.begin(16,2);
    screen.setCursor(0, 0);    
    screen.backlight();
    screen.print(row1);
    screen.setCursor(0, 1);
    screen.print(row2);
}