#ifndef Controller_h
#define Controller_h

class Controller{
    public:
        Controller(int firstPin);
        int getPlayerInput();
    private:
        int A_btnpin;
        int B_btnpin;
        int C_btnpin;
        int _scl;
        int _sda;
};
#endif
