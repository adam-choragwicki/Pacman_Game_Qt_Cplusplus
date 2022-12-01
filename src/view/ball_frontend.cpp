#include "view/ball_frontend.h"

AbstractBallFrontend::AbstractBallFrontend(const AbstractBall* ball)
{
    ball_ = ball;
}

AbstractBallFrontend::~AbstractBallFrontend() = default;

FoodballFrontend::FoodballFrontend(const Foodball* foodball) : AbstractBallFrontend(foodball)
{

}

PowerballFrontend::PowerballFrontend(const Powerball* powerball) : AbstractBallFrontend(powerball)
{

}
