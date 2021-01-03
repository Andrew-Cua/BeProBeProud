#include "StepperMotor.h"

bool StepperMotor::move(int relative) {
    _targetStep += relative;
    _distanceToGo = _targetStep - _currentStep;
    return true;
}

bool StepperMotor::moveTo(int absolute) {
    _targetStep = absolute;
    _distanceToGo = _targetStep - _currentStep;
    return true;
}

bool StepperMotor::setSpeed(float speed) {
    _stepWidth = 1E6 / ((speed) * PULSES_PER_REV); 
    return true;
}


bool StepperMotor::lock() {
    _locked = true;
    return true;
}

bool StepperMotor::unlock() {
    _locked = false;
    return true;
}

bool StepperMotor::run() {
    if (_locked) {
        return false;
    }
    _currentTimestamp = micros();

    if (_currentTimestamp - _lastTimestamp >= _stepWidth && _distanceToGo != 0) {
        _lastTimestamp = _currentTimestamp;
        _distanceToGo = _targetStep - _currentStep;
        _direction = changeDirection(_distanceToGo);
        
        

        digitalWrite(_directionPin, (_direction > 0) ? HIGH : LOW);
        digitalWrite(_pulsePin, (_stepPulledHigh) ? LOW : HIGH);

        
        if (_stepPulledHigh == false) {
            _currentStep += _direction;
        }
        _stepPulledHigh = !_stepPulledHigh;
        

    }

    return true;
}


int StepperMotor::changeDirection(int distance) {
    if (distance > 0) {
        return 1;
    } 

    return -1;
}

bool StepperMotor::runAtSpeed(int direction) {
    if (_locked) {
        return false;
    }
    
    _currentTimestamp = micros();
    if (_currentTimestamp - _lastTimestamp >= _stepWidth) {
        _lastTimestamp = _currentTimestamp;
        _direction = changeDirection(direction);
        
        

        digitalWrite(_directionPin, (_direction > 0) ? HIGH : LOW);
        digitalWrite(_pulsePin, (_stepPulledHigh) ? LOW : HIGH);
        if (_stepPulledHigh == false) {
            _currentStep += _direction;
        }
        _stepPulledHigh = !_stepPulledHigh;
        
    }
    
    return true;
}


bool StepperMotor::setCurrentPosition(int pos) {
    _currentStep = pos;
    return true;
}

int StepperMotor::getCurrentPosition() {
    return _currentStep;
}


bool StepperMotor::isLocked() {
    return _locked;
}