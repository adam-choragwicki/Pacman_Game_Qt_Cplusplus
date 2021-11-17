#pragma once

#include "common.h"

class MovableCharacterInterface
{
public:
    MovableCharacterInterface(int x, int y, Direction initialDirection);

    virtual void advanceAnimation() = 0;
    virtual void startMovement() = 0;
    virtual void stopMovement() = 0;
    virtual void resumeMovement() = 0;
    virtual void reset() = 0;

    int getX() const {return x_;}
    int getY() const {return y_;}

    void setNextDirection(Direction direction) {nextDirection_ = direction;}

protected:
    void setCoordinates(int x, int y);

    void processNewDirection();
    void validateAndProcessMovement();
    void checkAndProcessGameAreaBoundaryReach();

    const int diameter_ = 30;
    const int offsetX_ = -15;
    const int offsetY_ = -15;

    const int normalSpeed_ = 6;
    const int reducedSpeed_ = 50;

    int x_;
    int y_;
    int animationState_;
    bool moving_;
    Direction direction_;
    Direction nextDirection_;
};
