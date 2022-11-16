#ifndef Controller_h
#define Controller_h
#include "Arduino.h"
#include <LiquidCrystal_I2C>

class Controller{
    public:
        Controller(int firstPin, int displayAddress );
        int A_btnpin;
        int B_btnpin;
        int C_btnpin;
        LiquidCrystal_I2C lcd();
        void setChips(int valChange);
    private:
        int _scl;
        int _sda;
        int chips;

};
// code goes here
#endif
