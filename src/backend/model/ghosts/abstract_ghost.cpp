#include "model/ghosts/abstract_ghost.h"
#include <QtGui/QPainter>

AbstractGhost::AbstractGhost(const Coordinates& coordinates, const Direction initialDirection) : MovableCharacter(coordinates, initialDirection), MovingObject(QRectF(0, 0, 30, 30))
{
    MovableCharacter::reset();
    scaredState_ = ScaredState::NO_SCARED;
}

AbstractGhost::~AbstractGhost() = default;

void AbstractGhost::reset()
{
    MovableCharacter::reset();
    scaredState_ = ScaredState::NO_SCARED;
}

bool AbstractGhost::isScared() const
{
    return (scaredState_ == ScaredState::SCARED_BLUE) || (scaredState_ == ScaredState::SCARED_WHITE);
}

bool AbstractGhost::isScaredWhite() const
{
    return scaredState_ == ScaredState::SCARED_WHITE;
}

bool AbstractGhost::isScaredBlue() const
{
    return scaredState_ == ScaredState::SCARED_BLUE;
}

void AbstractGhost::advanceAnimation()
{
    if(animationState_ > 2)
    {
        setAnimationState(0);
    }
    else
    {
        ++animationState_;
    }
}

void AbstractGhost::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    CustomGraphicsItem::paint(painter, option, widget);

    const QRect boundingRect = MovableCharacter::rect_;
    const int animationState = animationState_;

    if(!isScared())
    {
        switch(getDirection())
        {
            case Direction::LEFT:
                if(animationState == 0)
                {
                    painter->drawPixmap(boundingRect, left1Pixmap_);
                }
                else
                {
                    painter->drawPixmap(boundingRect, left2Pixmap_);
                }
                break;

            case Direction::RIGHT:
                if(animationState == 0)
                {
                    painter->drawPixmap(boundingRect, right1Pixmap_);
                }
                else
                {
                    painter->drawPixmap(boundingRect, right2Pixmap_);
                }
                break;

            case Direction::DOWN:
                if(animationState == 0)
                {
                    painter->drawPixmap(boundingRect, down1Pixmap_);
                }
                else
                {
                    painter->drawPixmap(boundingRect, down2Pixmap_);
                }
                break;

            case Direction::UP:
                if(animationState == 0)
                {
                    painter->drawPixmap(boundingRect, up1Pixmap_);
                }
                else
                {
                    painter->drawPixmap(boundingRect, up2Pixmap_);
                }
                break;
        }
    }
    else if(isScaredBlue())
    {
        if(animationState == 0)
        {
            painter->drawPixmap(boundingRect, scaredBlue1Pixmap_);
        }
        else
        {
            painter->drawPixmap(boundingRect, scaredBlue2Pixmap_);
        }
    }
    else if(isScaredWhite())
    {
        if(animationState == 0)
        {
            painter->drawPixmap(boundingRect, scaredWhite1Pixmap_);
        }
        else
        {
            painter->drawPixmap(boundingRect, scaredWhite2Pixmap_);
        }
    }
}

void AbstractGhost::loadImages(const std::array<std::string, 12>& imagesUrls)
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
        const auto&[pixmap, path] = pixmapToPathPair;
        return pixmap->load(QString::fromStdString(path));
    };

    if(!std::all_of(pixmapToPathMapping.cbegin(), pixmapToPathMapping.cend(), loadImage))
    {
        throw std::runtime_error("Error, cannot load ghost images");
    }
}
