#include "LimitSwitch.h"


void LimitSwitch::update() {
    if (digitalRead(_pin) == LOW && !_limitSwitchHit) {
        onHit();
        _limitSwitchHit = true;
    } else {
        _limitSwitchHit = false;
    }
}


void LimitSwitch::onLimitSwitchHit(void handler(void)) {
    onHit = handler;
}