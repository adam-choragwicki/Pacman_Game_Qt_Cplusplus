#include "ball.h"

AbstractBall::AbstractBall(const Coordinates& coordinates) : coordinates_(coordinates)
{
    eaten_ = false;
}

AbstractBall::~AbstractBall() = default;

Foodball::Foodball(const Coordinates& coordinates) : AbstractBall(coordinates)
{

}

Powerball::Powerball(const Coordinates& coordinates) : AbstractBall(coordinates)
{

}
