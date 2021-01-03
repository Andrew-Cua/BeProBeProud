#ifndef SQUARE_H
#define SQUARE_H

/**
 * represents a sqaure on the playing field.
 * each has an x,y defined as its center with some
 * width defined as the distance between the center a side.
 */
typedef struct {
    int x;
    int y;
    int width;
    bool containsGameObject = false;
} Square;

#endif