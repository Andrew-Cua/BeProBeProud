#ifndef SPEED_CURVE_H
#define SPEED_CURVE_H
typedef struct SpeedCurve {
    float startPos;
    float endPos;
    float accel;
    float velMax; 
    float curVel = 0;
};


float computeSpeed(SpeedCurve* curve, int step) {
    
    
}
#endif