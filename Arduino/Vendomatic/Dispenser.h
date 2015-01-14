#include "Arduino.h"

class Dispenser {
    public:
        void dispenseItem(int row);
        void setupPins();
    private:
        void sendDataPacket(int row);
};
