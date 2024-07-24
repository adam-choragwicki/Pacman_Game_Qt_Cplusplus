#include "model/ghosts/abstract_ghost.h"
#include <QtGui/QPainter>
#include "config.h"
#include "model/ghost_timing_manager.h"

AbstractGhost::AbstractGhost(const Coordinates& coordinates, const Direction initialDirection, const std::chrono::seconds& moveOutOfTheStartingBoxTimeout) : MovableCharacter(coordinates, initialDirection)
{
    if(!commonPixmapsInitialized_)
    {
        loadCommonPixmaps();
        commonPixmapsInitialized_ = true;
    }

    ghostTimingManager_ = new GhostTimingManager(moveOutOfTheStartingBoxTimeout);

    MovableCharacter::reset();
    scaredState_ = ScaredState::NO_SCARED;

    movementTimer_.setInterval(Config::Timing::MovableCharacter::NORMAL_SPEED);
    movementTimer_.setSingleShot(true);

    drawRect_ = true;
}

AbstractGhost::~AbstractGhost() = default;

void AbstractGhost::reset()
{
    MovableCharacter::reset();
    scaredState_ = ScaredState::NO_SCARED;
}

bool AbstractGhost::isScared() const
{
    return scaredState_ != ScaredState::NO_SCARED;
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

    const QRect boundingRect = CustomGraphicsItem::boundingRect().toRect();

    if(scaredState_ == ScaredState::NO_SCARED)
    {
        switch(getDirection())
        {
            case Direction::LEFT:
                if(animationState_ == 0)
                {
                    painter->drawPixmap(boundingRect, left1Pixmap_);
                }
                else
                {
                    painter->drawPixmap(boundingRect, left2Pixmap_);
                }
                break;

            case Direction::RIGHT:
                if(animationState_ == 0)
                {
                    painter->drawPixmap(boundingRect, right1Pixmap_);
                }
                else
                {
                    painter->drawPixmap(boundingRect, right2Pixmap_);
                }
                break;

            case Direction::DOWN:
                if(animationState_ == 0)
                {
                    painter->drawPixmap(boundingRect, down1Pixmap_);
                }
                else
                {
                    painter->drawPixmap(boundingRect, down2Pixmap_);
                }
                break;

            case Direction::UP:
                if(animationState_ == 0)
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
    else if(scaredState_ == ScaredState::SCARED_BLUE)
    {
        if(animationState_ == 0)
        {
            painter->drawPixmap(boundingRect, *scaredBlue1Pixmap_);
        }
        else
        {
            painter->drawPixmap(boundingRect, *scaredBlue2Pixmap_);
        }
    }
    else if(scaredState_ == ScaredState::SCARED_WHITE)
    {
        if(animationState_ == 0)
        {
            painter->drawPixmap(boundingRect, *scaredWhite1Pixmap_);
        }
        else
        {
            painter->drawPixmap(boundingRect, *scaredWhite2Pixmap_);
        }
    }
    else
    {
        throw std::runtime_error("Cannot draw Ghost, wrong scared state");
    }
}

void AbstractGhost::loadImages(const std::array<std::string, 8>& imagesUrls)
{
    const std::map<QPixmap*, std::string> pixmapToPathMapping{{&left1Pixmap_,  imagesUrls.at(0)},
                                                              {&left2Pixmap_,  imagesUrls.at(1)},

                                                              {&right1Pixmap_, imagesUrls.at(2)},
                                                              {&right2Pixmap_, imagesUrls.at(3)},

                                                              {&up1Pixmap_,    imagesUrls.at(4)},
                                                              {&up2Pixmap_,    imagesUrls.at(5)},

                                                              {&down1Pixmap_,  imagesUrls.at(6)},
                                                              {&down2Pixmap_,  imagesUrls.at(7)}};

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

void AbstractGhost::setScared()
{
    scaredState_ = ScaredState::SCARED_BLUE;
    isSlowedDown_ = true;

    connect(&ghostTimingManager_->getScaredBlueStateTimer(), &QTimer::timeout, [this]()
    {
        qDebug() << "Scared blue state timeout";

        scaredState_ = ScaredState::SCARED_WHITE;

        connect(&ghostTimingManager_->getScaredWhiteStateTimer(), &QTimer::timeout, [this]()
        {
            qDebug() << "Scared white state timeout";

            scaredState_ = ScaredState::NO_SCARED;
            isSlowedDown_ = false;
        });

        ghostTimingManager_->startScaredWhiteTimer();
    });

    ghostTimingManager_->startScaredBlueTimer();
}

void AbstractGhost::loadCommonPixmaps()
{
    scaredBlue1Pixmap_ = std::make_unique<QPixmap>();
    scaredBlue2Pixmap_ = std::make_unique<QPixmap>();
    scaredWhite1Pixmap_ = std::make_unique<QPixmap>();
    scaredWhite2Pixmap_ = std::make_unique<QPixmap>();

    auto loadImage = [](const std::pair<QPixmap*, std::string>& pixmapToPathPair)
    {
        const auto&[pixmap, path] = pixmapToPathPair;
        return pixmap->load(QString::fromStdString(path));
    };

    const std::map<QPixmap*, std::string> pixmapToPathMapping{{scaredBlue1Pixmap_.get(),  ":/ghost/ghost_scared_blue_1.png"},
                                                              {scaredBlue2Pixmap_.get(),  ":/ghost/ghost_scared_blue_2.png"},
                                                              {scaredWhite1Pixmap_.get(), ":/ghost/ghost_scared_white_1.png"},
                                                              {scaredWhite2Pixmap_.get(), ":/ghost/ghost_scared_white_2.png"}};

    if(!std::all_of(pixmapToPathMapping.cbegin(), pixmapToPathMapping.cend(), loadImage))
    {
        throw std::runtime_error("Error, cannot load ghost static images");
    }
}
