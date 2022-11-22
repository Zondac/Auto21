/**
 * Displays text sent over the serial port (e.g. from the Serial Monitor) on
 * an attached LCD.
 */


#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display


LiquidCrystal_I2C lcd[4]={
  LiquidCrystal_I2C(0x27,16,2),
  LiquidCrystal_I2C(0x26,16,2),
  LiquidCrystal_I2C(0x25,16,2),
  LiquidCrystal_I2C(0x3F,16,2)
};

String inputBuffer;


int btns[12];
for (int declarepin = 22; declarepin <= 34; declarepin++)
{
  btns[declarepin-22] = declarepin;
}


void setup()
{
  for (int i = 0; i<4; i++){
    lcd[i].begin();
    lcd[i].backlight();
    lcd[i].clear();
    lcd[i].setCursor(0,0);
    lcd[i].print("Chips:");
    lcd[i].setCursor(0,1);
    lcd[i].noCursor();
  }
  for (size_t i = 22; i <= 34; i++)
  {
    pinMode(i,INPUT_PULLUP);
  }
  // Initialize the serial port at a speed of 9600 baud
	Serial.begin(9600);
}

  
void loop()
{
  int p1btn1prev = p1btn1;
  int p1btn2prev = p1btn2;
  int p1btn3prev = p1btn3;
  p1btn1 = digitalRead(3);
  p1btn2 = digitalRead(4);
  p1btn3 = digitalRead(2);
  if (p1btn1==LOW && p1btn1prev ==HIGH) Serial.println("p1.A");
  if (p1btn2==LOW && p1btn1prev ==HIGH) Serial.println("p1.B");
  if (p1btn3==LOW && p1btn1prev ==HIGH) Serial.println("p1.C");
	if (Serial.available()) {
		// Wait a bit for the entire message to arrive
		// Clear the screen
   for (int i = 0; i<4; i++){
    lcd[i].setCursor(0,1);
   }
   
		// Write all characters received with the serial port to the LCD.
		while (Serial.available() > 0) {
      inputBuffer = Serial.readString();
      }
      switch (inputBuffer[0]){
        case 'q':
        
        
          inputBuffer.remove(0,1);
          lcd[0].print("                ");
          lcd[0].setCursor(0,1);
          lcd[0].print(inputBuffer);
        break;
        
        case 'w':
        
        inputBuffer.remove(0,1);
          lcd[1].print(inputBuffer);
        break;
        
        case 'e':
        
        inputBuffer.remove(0,1);
          lcd[2].print(inputBuffer);
        break;
        
        case 'r':
        
        inputBuffer.remove(0,1);
          lcd[3].print(inputBuffer);
        break;
      }
	}
}
