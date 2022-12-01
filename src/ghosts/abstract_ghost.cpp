#include "ghosts/abstract_ghost.h"

#include <QRandomGenerator>

AbstractGhost::AbstractGhost(const Coordinates& coordinates, std::chrono::seconds startTimeout, const GameMap& gameMap) : MovableCharacter(coordinates, Direction::UP, gameMap)
{
    startTimer_.setSingleShot(true);
    scaredBlueStateTimer_.setSingleShot(true);
    scaredWhiteStateTimer_.setSingleShot(true);

    startTimer_.setInterval(startTimeout);
    scaredBlueStateTimer_.setInterval(scaredBlueTime);
    scaredWhiteStateTimer_.setInterval(scaredWhiteTime);
    movementTimer_.setInterval(NORMAL_SPEED);

    startTimer_.callOnTimeout(this, &AbstractGhost::setLeaveStartingBox);

    QObject::connect(&scaredBlueStateTimer_, &QTimer::timeout, this, &AbstractGhost::transformToScaredWhite);
    QObject::connect(&scaredWhiteStateTimer_, &QTimer::timeout, this, &AbstractGhost::transformToNoScared);

    timeToLeaveStartingBox_ = false;
    scaredState_ = ScaredState::NO_SCARED;
    AbstractGhost::reset();
}

void AbstractGhost::reset()
{
    MovableCharacter::reset();
    direction_ = Direction::UP;
    scaredState_ = ScaredState::NO_SCARED;
    timeToLeaveStartingBox_ = false;

    startTimer_.start();
    movementTimer_.setInterval(NORMAL_SPEED);
    scaredBlueStateTimer_.stop();
    scaredWhiteStateTimer_.stop();
}

void AbstractGhost::advanceAnimation()
{
    if(animationState_ > 2)
    {
        animationState_ = 0;
    }
    else
    {
        animationState_++;
    }
}

void AbstractGhost::move(const Coordinates& pacmanCoordinates)
{
    const int pacmanX = pacmanCoordinates.x_;
    const int pacmanY = pacmanCoordinates.y_;

    if(moving_)
    {
        if((direction_ == Direction::RIGHT && coordinates_.y_ < pacmanY) || (direction_ == Direction::LEFT && coordinates_.y_ > pacmanY))
        {
            if(direction_ == Direction::LEFT && coordinates_.y_ > pacmanY)
            {
                setNextDirection(Direction::UP);
            }
            else if(direction_ == Direction::RIGHT && coordinates_.y_ < pacmanY)
            {
                setNextDirection(Direction::DOWN);
            }
        }
        else if((direction_ == Direction::DOWN && coordinates_.x_ < pacmanX) || (direction_ == Direction::UP && coordinates_.x_ > pacmanX))
        {
            if(direction_ == Direction::UP && coordinates_.x_ > pacmanX)
            {
                setNextDirection(Direction::LEFT);
            }
            else if(direction_ == Direction::DOWN && coordinates_.x_ < pacmanX)
            {
                setNextDirection(Direction::RIGHT);
            }
        }
    }
    else
    {
        direction_ = static_cast<Direction>(QRandomGenerator::global()->bounded(1, 4));
    }

    processNewDirection();
    validateAndProcessMovement();
    checkAndProcessGameAreaBoundaryReach();
    advanceAnimation();
}

bool AbstractGhost::isInsideStartingBox() const
{
    return ((coordinates_.x_ > 209 && coordinates_.x_ < 406) && (coordinates_.y_ > 252 && coordinates_.y_ < 384));
}

void AbstractGhost::moveInsideStartingBox()
{
    const int centerY = 318;
    const int maxVerticalMovementOffset = 15;

    if((coordinates_.y_ == centerY - maxVerticalMovementOffset) || (coordinates_.y_ == centerY + maxVerticalMovementOffset))
    {
        if(direction_ == Direction::UP)
        {
            direction_ = Direction::DOWN;
        }
        else if(direction_ == Direction::DOWN)
        {
            direction_ = Direction::UP;
        }
    }

    if(direction_ == Direction::UP)
    {
        coordinates_.y_ = coordinates_.y_ - 1;
    }
    else if(direction_ == Direction::DOWN)
    {
        coordinates_.y_ = coordinates_.y_ + 1;
    }
}

void AbstractGhost::moveOutOfStartingBox()
{
    const int centerX = 307;

    if(coordinates_.x_ > centerX)
    {
        coordinates_.x_ = coordinates_.x_ - 1;
    }
    else if(coordinates_.x_ < centerX)
    {
        coordinates_.x_ = coordinates_.x_ + 1;
    }

    if(coordinates_.x_ == centerX)
    {
        coordinates_.y_ = coordinates_.y_ - 1;
    }
}

void AbstractGhost::startMovement()
{
    startTimer_.start();
    movementTimer_.start();
}

void AbstractGhost::stopMovement()
{
    movementTimer_.stop();
}

void AbstractGhost::scare()
{
    scaredBlueStateTimer_.start();
    setScaredState(ScaredState::SCARED_BLUE);
    reduceSpeed();
}

void AbstractGhost::reduceSpeed()
{
    movementTimer_.setInterval(REDUCED_SPEED);
}

void AbstractGhost::resetSpeed()
{
    movementTimer_.setInterval(NORMAL_SPEED);
}

void AbstractGhost::transformToScaredWhite()
{
    setScaredState(AbstractGhost::ScaredState::SCARED_WHITE);
    scaredWhiteStateTimer_.start();
}

void AbstractGhost::transformToNoScared()
{
    setScaredState(AbstractGhost::ScaredState::NO_SCARED);
    resetSpeed();
}
