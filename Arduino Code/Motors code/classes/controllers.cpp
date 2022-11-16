#include "Arduino.h”
#include "controllers.h"
#include <LiquidCrystal_I2C.h>

Controller::Controller(int firstPin, int displayAddress) {
    A_btnpin = firstPin;
    B_btnpin = firstPin + 1;
    C_btnpin = firstPin + 2;
    lcd(displayAddress, 16,2);

    chips = 500;
    
    pinMode(A_btnpin, INPUT_PULLUP);
    pinMode(B_btnpin, INPUT_PULLUP);
    pinMode(C_btnpin, INPUT_PULLUP);
    lcd.print(chips);
    _sda = 20;
    _scl = 21;

}

void Controller::setChips(int valChange){
    chips += valChange;
    lcd.print(chips);
}