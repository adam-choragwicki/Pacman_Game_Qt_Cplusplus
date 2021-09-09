#include "movable_character_interface.h"
#include "game_map.h"

MovableCharacterInterface::MovableCharacterInterface(int x, int y, Direction initialDirection) : x_(x), y_(y), direction_(initialDirection)
{
    MovableCharacterInterface::reset();
}

void MovableCharacterInterface::reset()
{
    moving_ = false;
    nextDirection_ = Direction::none;
    animationState_ = 0;
}

void MovableCharacterInterface::setCoordinates(int x, int y)
{
    x_ = x;
    y_ = y;
}

void MovableCharacterInterface::processNewDirection()
{
    QPoint point;

    if(nextDirection_ != direction_)
    {
        switch(nextDirection_)
        {
        case Direction::left:
            point.setX(x_ - 1);
            point.setY(y_);

            if(GameMap::isPathPointValid(point))
            {
                direction_ = nextDirection_;
                nextDirection_ = Direction::none;
            }
            break;

        case Direction::right:
            point.setX(x_ + 1);
            point.setY(y_);
            if(GameMap::isPathPointValid(point))
            {
                direction_ = nextDirection_;
                nextDirection_ = Direction::none;
            }
            break;

        case Direction::up:
            point.setX(x_);
            point.setY(y_ - 1);
            if(GameMap::isPathPointValid(point))
            {
                direction_ = nextDirection_;
                nextDirection_ = Direction::none;
            }
            break;

        case Direction::down:
            point.setX(x_);
            point.setY(y_ + 1);
            if(GameMap::isPathPointValid(point))
            {
                direction_ = nextDirection_;
                nextDirection_ = Direction::none;
            }
            break;

        case Direction::none:
            break;
        }
    }
}

void MovableCharacterInterface::validateAndProcessMovement()
{
    QPoint point;

    switch(direction_)
    {
    case Direction::left:
        point.setX(x_ - 1);
        point.setY(y_);

        if(GameMap::isPathPointValid(point))
        {
            x_ = x_ - 1;
            moving_ = true;
        }
        else
        {
            moving_ = false;
        }
        break;

    case Direction::right:
        point.setX(x_ + 1);
        point.setY(y_);

        if(GameMap::isPathPointValid(point))
        {
            x_ = x_ + 1;
            moving_ = true;
        }
        else
        {
            moving_ = false;
        }
        break;

    case Direction::up:
        point.setX(x_);
        point.setY(y_ - 1);

        if(GameMap::isPathPointValid(point))
        {
            y_= y_ - 1;
            moving_ = true;
        }
        else
        {
            moving_ = false;
        }
        break;

    case Direction::down:
        point.setX(x_);
        point.setY(y_ + 1);

        if(GameMap::isPathPointValid(point))
        {
            y_= y_ + 1;
            moving_ = true;
        }
        else
        {
            moving_ = false;
        }
        break;

    case Direction::none:
        break;
    }
}

void MovableCharacterInterface::checkAndProcessGameAreaBoundaryReach()
{
    /*Teleportation when reached left boundary of middle horizontal line*/
    if(x_ <= 0)
    {
        x_ = 613;
        y_ = 318;
    }

    /*Teleportation when reached right boundary of middle horizontal line*/
    if(x_ >= 614)
    {
        x_ = 1;
        y_ = 318;
    }
}
