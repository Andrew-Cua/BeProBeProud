#include "TicTacToe.h"

Square TicTacToe::getLocale(int i, int j) {
    return _gameboard[i][j];
}

Square TicTacToe::getCurrentLocation() {
    return _currentLocation;
}

void TicTacToe::setCurrentLocation(int i, int j) {
    _currentLocation = _gameboard[i][j];
}

void TicTacToe::actuateEndEffector() {
    
}