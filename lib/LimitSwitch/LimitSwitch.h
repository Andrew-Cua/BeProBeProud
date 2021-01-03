#ifndef LIMIT_SWITCH_H
#define LIMIT_SWITCH_H
#include "Arduino.h"
class LimitSwitch {
private:
    bool _limitSwitchHit = false;
    void (*onHit) (void);
    int _pin;
public:
    LimitSwitch(int pin) : _pin(pin) {
        pinMode(_pin, INPUT_PULLUP);
    }

    /**
     * check the status of the switch.
     */
    void update();

    /**
     * sets what code should run if the switch has been hit.
     */
    void onLimitSwitchHit(void handler(void));    
};


#endif