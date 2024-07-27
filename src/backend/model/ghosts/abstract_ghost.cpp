#include "model/ghosts/abstract_ghost.h"
#include <QtGui/QPainter>
#include "config.h"
#include "model/ghost_timing_manager.h"
#include "pixmap_loader.h"

AbstractGhost::AbstractGhost(const Coordinates& coordinates, const Direction initialDirection, const std::chrono::seconds& moveOutOfTheStartingBoxTimeout) : MovableCharacter(coordinates, initialDirection)
{
    if(!commonPixmapsInitialized_)
    {
        loadCommonPixmaps();
        commonPixmapsInitialized_ = true;
    }

    ghostTimingManager_ = std::make_unique<GhostTimingManager>(moveOutOfTheStartingBoxTimeout);

    MovableCharacter::reset();
    scaredState_ = ScaredState::NO_SCARED;

    drawRect_ = true;
}

AbstractGhost::~AbstractGhost() = default;

void AbstractGhost::reset()
{
    MovableCharacter::reset();
    ghostTimingManager_->reset();
    scaredState_ = ScaredState::NO_SCARED;
    isSlowedDown_ = false;
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

    const QPixmap* pixmap;

    static const QPixmap* normalPixmaps[4][2] = {{&left1Pixmap_,  &left2Pixmap_},   // LEFT
                                                 {&right1Pixmap_, &right2Pixmap_}, // RIGHT
                                                 {&down1Pixmap_,  &down2Pixmap_},   // DOWN
                                                 {&up1Pixmap_,    &up2Pixmap_}        // UP
    };

    static const QPixmap* scaredBluePixmaps[2] = {scaredBlue1Pixmap_.get(), scaredBlue2Pixmap_.get()};

    static const QPixmap* scaredWhitePixmaps[2] = {scaredWhite1Pixmap_.get(), scaredWhite2Pixmap_.get()};

    const QPixmap* pixmap;
    const int phase = animationState_ % 2;

    if(scaredState_ == ScaredState::NO_SCARED)
    {
        switch(direction_)
        {
            case Direction::LEFT:
                if(phase == 0)
                {
                    pixmap = &left1Pixmap_;
                }
                else
                {
                    pixmap = &left2Pixmap_;
                }
                break;

            case Direction::RIGHT:
                if(phase == 0)
                {
                    pixmap = &right1Pixmap_;
                }
                else
                {
                    pixmap = &right2Pixmap_;
                }
                break;

            case Direction::DOWN:
                if(phase == 0)
                {
                    pixmap = &down1Pixmap_;
                }
                else
                {
                    pixmap = &down2Pixmap_;
                }
                break;

            case Direction::UP:
                if(phase == 0)
                {
                    pixmap = &up1Pixmap_;
                }
                else
                {
                    pixmap = &up2Pixmap_;
                }
                break;

            default:
                throw std::runtime_error("Cannot draw Ghost, wrong direction");
        }
    }
    else if(scaredState_ == ScaredState::SCARED_BLUE)
    {
        if(phase == 0)
        {
            pixmap = scaredBlue1Pixmap_.get();
        }
        else
        {
            pixmap = scaredBlue2Pixmap_.get();
        }
    }
    else if(scaredState_ == ScaredState::SCARED_WHITE)
    {
        if(phase == 0)
        {
            pixmap = scaredWhite1Pixmap_.get();
        }
        else
        {
            pixmap = scaredWhite2Pixmap_.get();
        }
    }
    else
    {
        throw std::runtime_error("Cannot draw Ghost, wrong scared state");
    }

    painter->drawPixmap(rect_.toRect(), *pixmap);
}

void AbstractGhost::loadPixmaps(const std::array<QString, 8>& imagesUrls)
{
    const std::vector<PixmapLoader::PixmapEntry> pixmapEntries{{&left1Pixmap_,  imagesUrls.at(0)},
                                                               {&left2Pixmap_,  imagesUrls.at(1)},

                                                               {&right1Pixmap_, imagesUrls.at(2)},
                                                               {&right2Pixmap_, imagesUrls.at(3)},

                                                               {&up1Pixmap_,    imagesUrls.at(4)},
                                                               {&up2Pixmap_,    imagesUrls.at(5)},

                                                               {&down1Pixmap_,  imagesUrls.at(6)},
                                                               {&down2Pixmap_,  imagesUrls.at(7)}};

    PixmapLoader::loadPixmaps(pixmapEntries);
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

    const std::vector<PixmapLoader::PixmapEntry> pixmapEntries = {{scaredBlue1Pixmap_.get(),  ":/ghosts/scared_blue/ghost_scared_blue_1.png"},
                                                                  {scaredBlue2Pixmap_.get(),  ":/ghosts/scared_blue/ghost_scared_blue_2.png"},
                                                                  {scaredWhite1Pixmap_.get(), ":/ghosts/scared_white/ghost_scared_white_1.png"},
                                                                  {scaredWhite2Pixmap_.get(), ":/ghosts/scared_white/ghost_scared_white_2.png"}};

    PixmapLoader::loadPixmaps(pixmapEntries);
}
