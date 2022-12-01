#pragma once

#include "ball.h"

class AbstractBallFrontend
{
public:
    explicit AbstractBallFrontend(const AbstractBall* ball);
    virtual ~AbstractBallFrontend() = 0;

    [[nodiscard]] const AbstractBall* getBall() const
    { return ball_; }

private:
    const AbstractBall* ball_;
};

class FoodballFrontend : public AbstractBallFrontend
{
public:
    explicit FoodballFrontend(const Foodball* foodball);

    static const int DIAMETER = 7;
};

class PowerballFrontend : public AbstractBallFrontend
{
public:
    explicit PowerballFrontend(const Powerball* powerball);

    static const int DIAMETER = 15;
};
