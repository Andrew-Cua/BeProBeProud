#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H
#include <GameBase.h>
#include <StepperMotor.h>

class TicTacToe : public GameBase {
public:
    TicTacToe() : GameBase(3, 3) {

        
        _gameboard = new Square*[_height];
        for (int i = 0; i < 3; i++) {
            _gameboard[i] = new Square[_width];
        }

        for (int i = 0; i < _height; i++) {
            for (int j = 0; j < _width; j++) {
                _gameboard[i][j].x = (3200 + (6400 * j) - 1000); //TODO figure out the actual spacing of the game, consult engineering for more details 
                _gameboard[i][j].y = (3200 + (6400 * i) - 1000);
                _gameboard[i][j].width = 0;  
            }
        }

        _currentLocation = _gameboard[0][0];
    }
    Square getLocale(int i, int j);
    Square getCurrentLocation();
    void setCurrentLocation(int i, int j);
    void actuateEndEffector();

};

#endif