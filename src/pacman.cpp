#include "game_map.h"
#include "pacman.h"
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QDebug>

Pacman::Pacman() : MovableCharacterInterface(startingX_, startingY_, Direction::left)
{
    movementTimer_.setInterval(MovableCharacterInterface::normalSpeed_);
    loadImages();
    Pacman::reset();
}

void Pacman::reset()
{
    MovableCharacterInterface::reset();
    direction_ = Direction::left;
    setCoordinates(startingX_, startingY_);
}

void Pacman::advanceAnimation()
{
    if(moving_)
    {
        if(animationState_ >= 8 * animationSpeedFactor_)
        {
            animationState_ = 0;
        }
        else
        {
            animationState_++;
        }
    }
}

void Pacman::loadImages()
{
    assert(left1Pixmap_.load(":/pacman/images/pacman/pacman_left_close.png"));
    assert(left2Pixmap_.load(":/pacman/images/pacman/pacman_left_open_1.png"));
    assert(left3Pixmap_.load(":/pacman/images/pacman/pacman_left_open_2.png"));
    assert(left4Pixmap_.load(":/pacman/images/pacman/pacman_left_open_3.png"));

    assert(right1Pixmap_.load(":/pacman/images/pacman/pacman_right_close.png"));
    assert(right2Pixmap_.load(":/pacman/images/pacman/pacman_right_open_1.png"));
    assert(right3Pixmap_.load(":/pacman/images/pacman/pacman_right_open_2.png"));
    assert(right4Pixmap_.load(":/pacman/images/pacman/pacman_right_open_3.png"));

    assert(up1Pixmap_.load(":/pacman/images/pacman/pacman_up_close.png"));
    assert(up2Pixmap_.load(":/pacman/images/pacman/pacman_up_open_1.png"));
    assert(up3Pixmap_.load(":/pacman/images/pacman/pacman_up_open_2.png"));
    assert(up4Pixmap_.load(":/pacman/images/pacman/pacman_up_open_3.png"));

    assert(down1Pixmap_.load(":/pacman/images/pacman/pacman_down_close.png"));
    assert(down2Pixmap_.load(":/pacman/images/pacman/pacman_down_open_1.png"));
    assert(down3Pixmap_.load(":/pacman/images/pacman/pacman_down_open_2.png"));
    assert(down4Pixmap_.load(":/pacman/images/pacman/pacman_down_open_3.png"));
}

void Pacman::startMovement()
{
    movementTimer_.start();
}

void Pacman::stopMovement()
{
    movementTimer_.stop();
}

void Pacman::resumeMovement()
{
    movementTimer_.start();
}

void Pacman::move()
{
    processNewDirection();
    validateAndProcessMovement();
    checkAndProcessGameAreaBoundaryReach();
}

QRectF Pacman::boundingRect() const
{
    return QRect(x_ + offsetX_, y_ + offsetY_, diameter_, diameter_);
}

void Pacman::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    QRect boundingRect(x_ + offsetX_, y_ + offsetY_, diameter_, diameter_);

    switch(direction_)
    {
    case Direction::left:
        if(animationState_ < 2 * animationSpeedFactor_)
        {
            painter->drawPixmap(boundingRect, left1Pixmap_);
        }
        else if(animationState_ < 4 * animationSpeedFactor_)
        {
            painter->drawPixmap(boundingRect, left2Pixmap_);
        }
        else if(animationState_ < 6 * animationSpeedFactor_)
        {
            painter->drawPixmap(boundingRect, left3Pixmap_);
        }
        else if(animationState_ <= 8 * animationSpeedFactor_)
        {
            painter->drawPixmap(boundingRect, left4Pixmap_);
        }
        else
        {
            qDebug() << "LEFT NOTHING=" << animationState_;
        }
        break;

    case Direction::right:
        if(animationState_ < 2 * animationSpeedFactor_)
        {
            painter->drawPixmap(boundingRect, right1Pixmap_);
        }
        else if(animationState_ < 4 * animationSpeedFactor_)
        {
            painter->drawPixmap(boundingRect, right2Pixmap_);
        }
        else if(animationState_ < 6 * animationSpeedFactor_)
        {
            painter->drawPixmap(boundingRect, right3Pixmap_);
        }
        else if(animationState_ <= 8 * animationSpeedFactor_)
        {
            painter->drawPixmap(boundingRect, right4Pixmap_);
        }
        else
        {
            qDebug() << "RIGHT NOTHING=" << animationState_;
        }
        break;

    case Direction::up:
        if(animationState_ < 2 * animationSpeedFactor_)
        {
            painter->drawPixmap(boundingRect ,up1Pixmap_);
        }
        else if(animationState_ < 4 * animationSpeedFactor_)
        {
            painter->drawPixmap(boundingRect, up2Pixmap_);
        }
        else if(animationState_ < 6 * animationSpeedFactor_)
        {
            painter->drawPixmap(boundingRect, up3Pixmap_);
        }
        else if(animationState_ <= 8 * animationSpeedFactor_)
        {
            painter->drawPixmap(boundingRect, up4Pixmap_);
        }
        else
        {
            qDebug() << "UP NOTHING=" << animationState_;
        }
        break;

    case Direction::down:
        if(animationState_ < 2 * animationSpeedFactor_)
        {
            painter->drawPixmap(boundingRect, down1Pixmap_);
        }
        else if(animationState_ < 4 * animationSpeedFactor_)
        {
            painter->drawPixmap(boundingRect, down2Pixmap_);
        }
        else if(animationState_ < 6 * animationSpeedFactor_)
        {
            painter->drawPixmap(boundingRect, down3Pixmap_);
        }
        else if(animationState_ <= 8 * animationSpeedFactor_)
        {
            painter->drawPixmap(boundingRect, down4Pixmap_);
        }
        else
        {
            qDebug() << "DOWN NOTHING=" << animationState_;;
        }
        break;

    case Direction::none:
        qDebug() << "NONE";
        break;
    }
}
