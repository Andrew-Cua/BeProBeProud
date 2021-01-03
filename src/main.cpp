#include <Arduino.h>
#include <StepperMotor.h>
#include <PositionableMotor.h>
#include <LimitSwitch.h>
#include <GameBase.h>
#include <TicTacToe.h>

//TODO: sort these into their own classes
void onXLimitSwitchLow(void);
void onYLimitSwitchLow(void);
void handleXMovement(void);
void handleYMovement(void);
void computeLocation(void);
int applyDeadband(int x, int bound, int nominalValue);

PositionableMotor* mtr_ptr;
PositionableMotor* mtr2_ptr;
PositionableMotor* mtr3_ptr;

GameBase* game;

StepperMotor motor(4,5);
StepperMotor motor2(6,7);
StepperMotor motor3(8,9);
TicTacToe ticTacToe;
LimitSwitch xlimit(2);

int currentX = 0;
int currentY = 0;
bool hasXChanged = false;
bool hasYChanged = false;

void setup() {
  mtr_ptr = &motor;
  mtr2_ptr = &motor2;
  mtr3_ptr = &motor3;

  game = &ticTacToe;
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  mtr_ptr -> setSpeed(5);
  mtr2_ptr -> setSpeed(5);
  mtr3_ptr -> setSpeed(5);
  xlimit.onLimitSwitchHit(onXLimitSwitchLow);
}

void loop() {
  // put your main code here, to run repeatedly:
  //handleXMovement();
  //handleYMovement();
  computeLocation();

  game -> setCurrentLocation(currentX, currentY);
  Square target = game -> getCurrentLocation();

  mtr_ptr -> moveTo(target.x);
  mtr2_ptr -> moveTo(target.x);
  mtr3_ptr -> moveTo(target.y);

  mtr_ptr -> run();
  mtr2_ptr -> run();
  mtr3_ptr -> run();
  xlimit.update();
}



void onXLimitSwitchLow(void) {
  mtr_ptr -> moveTo(0);
  mtr2_ptr -> moveTo(0);
  mtr_ptr -> setCurrentPosition(0);
  //mtr_ptr -> lock();
  mtr2_ptr -> setCurrentPosition(0);
  //mtr2_ptr -> lock();
}

void onYLimitSwitchLow() {
  mtr3_ptr -> setCurrentPosition(0);
  mtr3_ptr -> moveTo(0);
  //mtr3_ptr -> lock();
}

//TODO: analogRead has 100us latency on ATMega devies and 400us on ATSamd Devices, find a work around for this. 



void handleXMovement() {
  int pos = analogRead(A1) - 512;
  float fPos = (float)(abs(pos));
  float speed = ((fPos / (float)512) * (float)10);

  mtr_ptr -> setSpeed(speed);
  mtr2_ptr -> setSpeed(speed);

  if (!(abs(pos) > 0 && abs(pos) < 60) && !mtr_ptr -> isLocked() && digitalRead(2) != LOW) {
    mtr_ptr -> runAtSpeed(pos);
    mtr2_ptr -> runAtSpeed(pos);
  } else if (mtr_ptr -> isLocked() || digitalRead(2) == LOW) {
    if (pos > 0) {
      mtr_ptr -> unlock();
      mtr_ptr -> runAtSpeed(pos);
      mtr2_ptr -> unlock();
      mtr2_ptr -> runAtSpeed(pos);
    }


  } 
}

void handleYMovement() {
  int posY = analogRead(A0) - 512;
  float fPosY = (float)(abs(posY));
  float speedY = ((fPosY / (float)512) * (float)10);
  mtr3_ptr -> setSpeed(speedY);

  mtr3_ptr -> runAtSpeed(posY);


}


/**
 * changes the desired location of the end affector based on user-input.
 * treats an analog devices as a switch for now. 
 * 
 * TODO: find out if it can just be connected to a digital pin somehow, might need a driver circuit of somekind. 
 */
void computeLocation() {
  int posX = applyDeadband(analogRead(A1) - 512, 75, 0);
  int posY = applyDeadband(analogRead(A0) - 512, 75, 0);

  if (abs(posX) >= 250 && !hasXChanged) {
    currentX += (posX > 0) ? 1 : -1;
    hasXChanged = true;

    //keep x in bounds
    if (currentX > 2) {
      currentX = 2;
    } else if (currentX < 0) {
      currentX = 0;
    }
    
  } 

  if (abs(posY) >= 250 && !hasYChanged) {
    currentY += (posY > 0) ? 1 : -1;
    hasYChanged = true;

    // keep y in bounds
    if (currentY > 2) {
      currentY = 2;
    } else if (currentY < 0) {
      currentY = 0;
    }

  }

  if (posX == 0 && hasXChanged) {
    hasXChanged = false;
  }

  if (posY == 0 && hasYChanged) {
    hasYChanged = false;
  }
}


int applyDeadband(int x, int bound, int nominalValue) {
  if (abs(x) < bound) {
    return nominalValue;
  }

  return x;
}