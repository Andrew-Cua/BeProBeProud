#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H
#include "Arduino.h"
#include "PositionableMotor.h"
const int PULSES_PER_REV = 800;

class StepperMotor : public PositionableMotor {
    private:
        int _currentStep = 0;
        int _targetStep = 0;
        int _speed = 0;
        int _distanceToGo = 0;
        int _direction = 1; // positive is CW, negative is CCW
        float _stepWidth = 7.5;

        unsigned long _currentTimestamp = 0;
        unsigned long _lastTimestamp = 0;
        bool _locked = false;
        bool _stepPulledHigh = false;

        const int _directionPin;
        const int _pulsePin;

        int changeDirection(int distance);
    
    public:
        StepperMotor(int directionPin, int pulsePin) : _directionPin(directionPin), _pulsePin(pulsePin) {
            pinMode(_directionPin, OUTPUT);
            pinMode(_pulsePin, OUTPUT);
        }

        bool move(int relative);
        bool moveTo(int absolute);
        bool setSpeed(float speed);
        bool run();
        bool lock();
        bool unlock();
        bool runAtSpeed(int direction);
        bool setCurrentPosition(int pos);
        int  getCurrentPosition();
        bool isLocked();

};
#endif