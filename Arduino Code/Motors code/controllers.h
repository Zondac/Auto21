#ifndef Controller_h
#define Controller_h

class Controller{
    public:
        Controller(int firstPin);
        int A_btnpin;
        int B_btnpin;
        int C_btnpin;
        char getPlayerInput();
    private:
        int _scl;
        int _sda;
};
#endif
