#include "ghost_base.h"
#include "game_map.h"
#include "pacman.h"
#include "drawer.h"

#include <QRandomGenerator>

GhostBase::GhostBase(const Coordinates& coordinates, std::chrono::seconds startTimeout, const GameMap& gameMap) : MovableCharacterInterface(coordinates, Direction::up, gameMap)
{
    startTimer_.setSingleShot(true);
    scaredBlueStateTimer_.setSingleShot(true);
    scaredWhiteStateTimer_.setSingleShot(true);

    startTimer_.setInterval(startTimeout);
    scaredBlueStateTimer_.setInterval(scaredBlueTime);
    scaredWhiteStateTimer_.setInterval(scaredWhiteTime);
    movementTimer_.setInterval(MovableCharacterInterface::normalSpeed_);

    startTimer_.callOnTimeout(this, &GhostBase::setLeaveStartingBox);

    QObject::connect(&scaredBlueStateTimer_, &QTimer::timeout, this, &GhostBase::transformToScaredWhite);
    QObject::connect(&scaredWhiteStateTimer_, &QTimer::timeout, this, &GhostBase::transformToNoScared);

    timeToLeaveStartingBox_ = false;
    scaredState_ = ScaredState::noScared;
    GhostBase::reset();

    Drawer::drawItem(this);
}

GhostBase::~GhostBase()
{
    Drawer::eraseItem(this);
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

void GhostBase::move(const Coordinates& pacmanCoordinates)
{
    const int pacmanX = pacmanCoordinates.x_;
    const int pacmanY = pacmanCoordinates.y_;

    if(moving_)
    {
        if((direction_ == Direction::right && coordinates_.y_ < pacmanY) || (direction_ == Direction::left && coordinates_.y_ > pacmanY))
        {
            if(direction_ == Direction::left && coordinates_.y_ > pacmanY)
            {
                setNextDirection(Direction::up);
            }
            else if(direction_ == Direction::right && coordinates_.y_ < pacmanY)
            {
                setNextDirection(Direction::down);
            }
        }
        else if((direction_ == Direction::down && coordinates_.x_ < pacmanX) || (direction_ == Direction::up && coordinates_.x_ > pacmanX))
        {
            if(direction_ == Direction::up && coordinates_.x_ > pacmanX)
            {
                setNextDirection(Direction::left);
            }
            else if(direction_ == Direction::down && coordinates_.x_ < pacmanX)
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
    advanceAnimation();
}

bool GhostBase::isInsideStartingBox() const
{
    return ((coordinates_.x_ > 209 && coordinates_.x_ < 406) && (coordinates_.y_ > 252 && coordinates_.y_ < 384));
}

void GhostBase::moveInsideStartingBox()
{
    const int centerY = 318;
    const int maxVerticalMovementOffset = 15;

    if((coordinates_.y_ == centerY - maxVerticalMovementOffset) || (coordinates_.y_ == centerY + maxVerticalMovementOffset))
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
        coordinates_.y_ = coordinates_.y_ - 1;
    }
    else if(direction_ == Direction::down)
    {
        coordinates_.y_ = coordinates_.y_ + 1;
    }
}

void GhostBase::moveOutOfStartingBox()
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

void GhostBase::startMovement()
{
    startTimer_.start();
    movementTimer_.start();
}

void GhostBase::stopMovement()
{
    movementTimer_.stop();
}

void GhostBase::loadImages(const QVector<std::string>& imagesUrls)
{
    const std::map<QPixmap*, std::string> pixmapToPathMapping{{&left1Pixmap_,        imagesUrls.at(0)},
                                                              {&left2Pixmap_,        imagesUrls.at(1)},

                                                              {&right1Pixmap_,       imagesUrls.at(2)},
                                                              {&right2Pixmap_,       imagesUrls.at(3)},

                                                              {&up1Pixmap_,          imagesUrls.at(4)},
                                                              {&up2Pixmap_,          imagesUrls.at(5)},

                                                              {&down1Pixmap_,        imagesUrls.at(6)},
                                                              {&down2Pixmap_,        imagesUrls.at(7)},

                                                              {&scaredBlue1Pixmap_,  imagesUrls.at(8)},
                                                              {&scaredBlue2Pixmap_,  imagesUrls.at(9)},

                                                              {&scaredWhite1Pixmap_, imagesUrls.at(10)},
                                                              {&scaredWhite2Pixmap_, imagesUrls.at(11)}};

    auto loadImage = [](const std::pair<QPixmap*, std::string>& pixmapToPathPair)
    {
        return pixmapToPathPair.first->load(QString::fromStdString(pixmapToPathPair.second));
    };

    if(!std::all_of(pixmapToPathMapping.cbegin(), pixmapToPathMapping.cend(), loadImage))
    {
        throw std::runtime_error("Cannot load Ghost images");
    }
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
    return QRect(coordinates_.x_ + offsetX_, coordinates_.y_ + offsetY_, diameter_, diameter_);
}

void GhostBase::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    QRect boundingRect(coordinates_.x_ + offsetX_, coordinates_.y_ + offsetY_, diameter_, diameter_);

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
                throw std::runtime_error("Painting Ghost Direction::none");
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
}
