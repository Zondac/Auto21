#include "controllers.h"

Controller::Controller(int firstPin) {
    A_btnpin = firstPin;
    B_btnpin = firstPin + 1;
    C_btnpin = firstPin + 2;
    pinMode(A_btnpin, INPUT_PULLUP);
    pinMode(B_btnpin, INPUT_PULLUP);
    pinMode(C_btnpin, INPUT_PULLUP);
    _sda = 20;
    _scl = 21;
};

char Controller::getPlayerInput(){
    bool finished = false;
    while (!finished){
        if(digitalRead(A_btnpin)){
            return ('a');
        }
        else if (digitalRead(B_btnpin))
        {
            return ('b');
        }
        else if (digitalRead(C_btnpin))
        {
            return('c');
        }
    }

}