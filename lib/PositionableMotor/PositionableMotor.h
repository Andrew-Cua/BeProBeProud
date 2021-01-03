#ifndef POSITIONABLE_MOTOR_H
#define POSITIONABLE_MOTOR_H

/**
 * represents a motor with the capability to be controlled via position.
 */
class PositionableMotor {

    public:

        /**
         * moves the motor relative to its current position
         * 
         * @param relative the distance for the motor to travel
         * @return whether the function was successful in changing the setpoint
         */ 
        virtual bool move(int relative) = 0;

        /**
         * moves the motor to a certain position.
         * 
         * @param relative the position for the motor to travel to
         * @return whether the function was successful in changing the setpoint
         */ 
        virtual bool moveTo(int absolute) = 0;

        /**
         * the speed for the motor to travel at.
         * 
         * @param speed the speed of the motor
         * @return whether the function was successful in changing the speed
         */ 
        virtual bool setSpeed(float speed) = 0;

        /**
         * runs the motor till it reaches its setpoint.
         */ 
        virtual bool run() = 0;

        /**
         * locks the motor and prevents it from moving.
         */ 
        virtual bool lock() = 0;
        
        /**
         * unlocks the motor and allows it to move freely.
         */ 
        virtual bool unlock() = 0;

        /**
         * runs the motor at its given speed, should also keep track of its position. 
         * 
         * @param direction the direction for the motor to move in only cares for +/-
         * @return true if unlocked, false otherwise
         */
        virtual bool runAtSpeed(int direction) = 0;

        /**
         * sets the current position of the motor, used for zeroing.
         * does not move the motor, just changes where it thinks it is. 
         * 
         * @param pos the position of the motor
         * @return whether the function changed the current position of the motor.
         */
        virtual bool setCurrentPosition(int pos) = 0;

        /**
         * gets the current position of the motor. 
         * 
         * @return the position of the motor
         */
        virtual int getCurrentPosition() = 0;

        /**
         * is the motor locked or not. 
         * 
         * @return true if locked, false otherwise
         */
        virtual bool isLocked() = 0;
};
#endif