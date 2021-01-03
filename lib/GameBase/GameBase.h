#ifndef GAME_BASE_H
#define GAME_BASE_H
#include <Square.h>
#include <PositionableMotor.h>

/**
 * Base class for games using the BeProBePround XY gantry.
 */
class GameBase {
protected: 
    const int _width;
    const int _height;
    
    Square** _gameboard;

    Square _currentLocation;

public:

    /**
     * creates a new {@code GameBase} with a given width and height. 
     */
    GameBase(int width, int height) : _width(width), _height(height) {}

    /**
     * get positional data from a certain locale on the board.
     * 
     * @param i the row to look at
     * @param j the column to look at
     * @return a square with the positional data
     */
    virtual Square getLocale(int i, int j) = 0;

    /**
     * gets the current location the end affector is at and returns the 
     * relevent positional data. 
     * 
     * @return a square with the positional data
     */
    virtual Square getCurrentLocation() = 0;

    /**
     * sets the current location of the end affector. 
     * 
     * @param i the row the affector is at
     * @param j the colun the affector is at
     */
    virtual void setCurrentLocation(int i, int j) = 0;


};


#endif