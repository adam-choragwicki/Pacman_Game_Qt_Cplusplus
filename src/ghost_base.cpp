#include "ghost_base.h"
#include "game_map.h"
#include "pacman.h"
#include <QRandomGenerator>
#include <QDebug>

GhostBase::GhostBase(int x, int y, int startTimeout) : MovableCharacterInterface(x, y, Direction::up)
{
    startTimer_.setSingleShot(true);
    scaredBlueStateTimer_.setSingleShot(true);
    scaredWhiteStateTimer_.setSingleShot(true);

    startTimer_.setInterval(startTimeout);
    scaredBlueStateTimer_.setInterval(scaredBlueTime);
    scaredWhiteStateTimer_.setInterval(scaredWhiteTime);
    movementTimer_.setInterval(MovableCharacterInterface::normalSpeed_);

    startTimer_.callOnTimeout(this, &GhostBase::setLeaveStartingBox);

    connect(&scaredBlueStateTimer_, &QTimer::timeout, this, &GhostBase::transformToScaredWhite);
    connect(&scaredWhiteStateTimer_, &QTimer::timeout, this, &GhostBase::transformToNoScared);

    GhostBase::reset();
}

void GhostBase::reset()
{
    MovableCharacterInterface::reset();
    direction_ = Direction::up;
    scaredState_ = ScaredState::noScared;
    timeToLeaveStartingBox_ = false;

    startTimer_.start();
    movementTimer_.setInterval(normalSpeed_);
    scaredBlueStateTimer_.stop();
    scaredWhiteStateTimer_.stop();
}

void GhostBase::advanceAnimation()
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

void GhostBase::move(int pacmanX, int pacmanY)
{
    if(moving_)
    {
        if((direction_ == Direction::right && y_ < pacmanY) || (direction_ == Direction::left && y_ > pacmanY))
        {
            if(direction_ == Direction::left && y_ > pacmanY)
            {
                setNextDirection(Direction::up);
            }
            else if(direction_ == Direction::right && y_ < pacmanY)
            {
                setNextDirection(Direction::down);
            }
        }
        else if((direction_ == Direction::down && x_ < pacmanX) || (direction_ == Direction::up && x_ > pacmanX))
        {
            if(direction_ == Direction::up && x_ > pacmanX)
            {
                setNextDirection(Direction::left);
            }
            else if(direction_ == Direction::down && x_ < pacmanX)
            {
                setNextDirection(Direction::right);
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
}

bool GhostBase::isInsideStartingBox() const
{
    return ((x_ > 209 && x_ < 406) && (y_ > 252 && y_ < 384));
}

void GhostBase::moveInsideStartingBox()
{
    const int centerY = 318;
    const int  maxVerticalMovementOffset = 15;

    if(y_ == centerY - maxVerticalMovementOffset || y_ == centerY + maxVerticalMovementOffset)
    {
        if(direction_ == Direction::up)
        {
            direction_ = Direction::down;
        }
        else if(direction_ == Direction::down)
        {
            direction_ = Direction::up;
        }
    }

    if(direction_ == Direction::up)
    {
        y_ -= 1;
    }
    else if(direction_ == Direction::down)
    {
        y_ += 1;
    }
}

void GhostBase::moveOutOfStartingBox()
{
    const int centerX = 307;

    if(x_ > centerX)
    {
        x_ -= 1;
    }
    else if(x_ < centerX)
    {
        x_ += 1;
    }

    if(x_ == centerX)
    {
        y_ -= 1;
    }
}

void GhostBase::startMovement()
{
    startTimer_.start();
    movementTimer_.start();
}

void GhostBase::stopMovement()
{
    movementTimer_.stop();
}

void GhostBase::resumeMovement()
{
    movementTimer_.start();
}

void GhostBase::loadImages(QVector<QString> imagesUrls)
{
    assert(left1Pixmap_.load(imagesUrls.at(0)));
    assert(left2Pixmap_.load(imagesUrls.at(1)));
    assert(right1Pixmap_.load(imagesUrls.at(2)));
    assert(right2Pixmap_.load(imagesUrls.at(3)));
    assert(up1Pixmap_.load(imagesUrls.at(4)));
    assert(up2Pixmap_.load(imagesUrls.at(5)));
    assert(down1Pixmap_.load(imagesUrls.at(6)));
    assert(down2Pixmap_.load(imagesUrls.at(7)));

    assert(scaredBlue1Pixmap_.load(imagesUrls.at(8)));
    assert(scaredBlue2Pixmap_.load(imagesUrls.at(9)));
    assert(scaredWhite1Pixmap_.load(imagesUrls.at(10)));
    assert(scaredWhite2Pixmap_.load(imagesUrls.at(11)));
}

void GhostBase::scare()
{
    scaredBlueStateTimer_.start();
    setScaredState(ScaredState::scaredBlue);
    reduceSpeed();
}

void GhostBase::reduceSpeed()
{
    movementTimer_.setInterval(reducedSpeed_);
}

void GhostBase::resetSpeed()
{
    movementTimer_.setInterval(normalSpeed_);
}

void GhostBase::transformToScaredWhite()
{
    setScaredState(GhostBase::ScaredState::scaredWhite);
    scaredWhiteStateTimer_.start();
}

void GhostBase::transformToNoScared()
{
    setScaredState(GhostBase::ScaredState::noScared);
    resetSpeed();
}

QRectF GhostBase::boundingRect() const
{
    return QRect(x_ + offsetX_, y_ + offsetY_, diameter_, diameter_);
}

void GhostBase::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    QRect boundingRect(x_ + offsetX_, y_ + offsetY_, diameter_, diameter_);

    if(scaredState_ == ScaredState::noScared)
    {
        switch(direction_)
        {
        case Direction::left:
            if(animationState_ == 0)
            {
                painter->drawPixmap(boundingRect, left1Pixmap_);
            }
            else
            {
                painter->drawPixmap(boundingRect, left2Pixmap_);
            }
            break;

        case Direction::right:
            if(animationState_ == 0)
            {
                painter->drawPixmap(boundingRect, right1Pixmap_);
            }
            else
            {
                painter->drawPixmap(boundingRect, right2Pixmap_);
            }
            break;

        case Direction::down:
            if(animationState_ == 0)
            {
                painter->drawPixmap(boundingRect, down1Pixmap_);
            }
            else
            {
                painter->drawPixmap(boundingRect, down2Pixmap_);
            }
            break;

        case Direction::up:
            if(animationState_ == 0)
            {
                painter->drawPixmap(boundingRect, up1Pixmap_);
            }
            else
            {
                painter->drawPixmap(boundingRect, up2Pixmap_);
            }
            break;

        case Direction::none:
            break;
        }
    }
    else if(scaredState_ == ScaredState::scaredBlue)
    {
        if(animationState_ == 0)
        {
            painter->drawPixmap(boundingRect, scaredBlue1Pixmap_);
        }
        else
        {
            painter->drawPixmap(boundingRect, scaredBlue2Pixmap_);
        }
    }
    else if(scaredState_ == ScaredState::scaredWhite)
    {
        if(animationState_ == 0)
        {
            painter->drawPixmap(boundingRect, scaredWhite1Pixmap_);
        }
        else
        {
            painter->drawPixmap(boundingRect, scaredWhite2Pixmap_);
        }
    }
    else
    {
        assert(false);
    }
}
