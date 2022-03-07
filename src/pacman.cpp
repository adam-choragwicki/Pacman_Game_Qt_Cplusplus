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
    const std::map<QPixmap*, std::string> pixmapToPathMapping{{&left1Pixmap_,  ":/pacman/images/pacman/pacman_left_close.png"},
                                                          {&left2Pixmap_,  ":/pacman/images/pacman/pacman_left_open_1.png"},
                                                          {&left3Pixmap_,  ":/pacman/images/pacman/pacman_left_open_2.png"},
                                                          {&left4Pixmap_,  ":/pacman/images/pacman/pacman_left_open_3.png"},

                                                          {&right1Pixmap_, ":/pacman/images/pacman/pacman_right_close.png"},
                                                          {&right2Pixmap_, ":/pacman/images/pacman/pacman_right_open_1.png"},
                                                          {&right3Pixmap_, ":/pacman/images/pacman/pacman_right_open_2.png"},
                                                          {&right4Pixmap_, ":/pacman/images/pacman/pacman_right_open_3.png"},

                                                          {&up1Pixmap_,    ":/pacman/images/pacman/pacman_up_close.png"},
                                                          {&up2Pixmap_,    ":/pacman/images/pacman/pacman_up_open_1.png"},
                                                          {&up3Pixmap_,    ":/pacman/images/pacman/pacman_up_open_2.png"},
                                                          {&up4Pixmap_,    ":/pacman/images/pacman/pacman_up_open_3.png"},

                                                          {&down1Pixmap_,  ":/pacman/images/pacman/pacman_down_close.png"},
                                                          {&down2Pixmap_,  ":/pacman/images/pacman/pacman_down_open_1.png"},
                                                          {&down3Pixmap_,  ":/pacman/images/pacman/pacman_down_open_2.png"},
                                                          {&down4Pixmap_,  ":/pacman/images/pacman/pacman_down_open_3.png"}};

    auto loadImage = [](const std::pair<QPixmap*, std::string>& pixmapToPathPair) {
        return pixmapToPathPair.first->load(QString::fromStdString(pixmapToPathPair.second));
    };

    if(!std::all_of(pixmapToPathMapping.cbegin(), pixmapToPathMapping.cend(), loadImage))
    {
        throw std::runtime_error("Cannot load Pacman images");
    }
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
        break;

    case Direction::none:
        break;
    }
}
