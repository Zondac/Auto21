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

int getPlayerInput(){
    int Apress = digitalRead(A_btnpin);
    int Bpress = digitalRead(B_btnpin);
    int Cpress = digitalRead(C_btnpin);
    return (Apress + Bpress*10 + Cpress*100);
}