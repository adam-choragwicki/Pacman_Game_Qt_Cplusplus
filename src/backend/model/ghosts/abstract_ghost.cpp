#include "model/ghosts/abstract_ghost.h"
#include <QtGui/QPainter>
#include "config.h"
#include "model/ghost_timing_manager.h"
#include "pixmap_loader.h"

AbstractGhost::AbstractGhost(const Coordinates& coordinates, const Direction initialDirection, const std::chrono::seconds& moveOutOfTheStartingBoxTimeout) : MovableCharacter(coordinates, initialDirection)
{
    initializePixmaps();

    ghostTimingManager_ = std::make_unique<GhostTimingManager>(moveOutOfTheStartingBoxTimeout);

    MovableCharacter::reset();
    scaredState_ = ScaredState::NO_SCARED;

    drawRect_ = true;
}

AbstractGhost::~AbstractGhost() = default;

void AbstractGhost::initializePixmaps()
{
    if(!commonPixmapsInitialized_)
    {
        initializeCommonPixmaps();
        commonPixmapsInitialized_ = true;
    }

    //    leftPixmaps_[0] = &left1Pixmap_;
    //    leftPixmaps_[1] = &left2Pixmap_;
    //    rightPixmaps_[0] = &right1Pixmap_;
    //    rightPixmaps_[1] = &right2Pixmap_;
    //    downPixmaps_[0] = &down1Pixmap_;
    //    downPixmaps_[1] = &down2Pixmap_;
    //    upPixmaps_[0] = &up1Pixmap_;
    //    upPixmaps_[1] = &up2Pixmap_;

    //    scaredBluePixmaps_[0] = scaredBlue1Pixmap_.get();
    //    scaredBluePixmaps_[1] = scaredBlue2Pixmap_.get();
    //    scaredWhitePixmaps_[0] = scaredWhite1Pixmap_.get();
    //    scaredWhitePixmaps_[1] = scaredWhite2Pixmap_.get();
}

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
    const int animationPhase = animationState_ % 2;

    // Select the appropriate pixmap based on the current state and direction
    if(scaredState_ == ScaredState::NO_SCARED)
    {
        switch(direction_)
        {
            case Direction::LEFT:
                pixmap = &leftPixmaps_[animationPhase];
                break;
            case Direction::RIGHT:
                pixmap = &rightPixmaps_[animationPhase];
                break;
            case Direction::DOWN:
                pixmap = &downPixmaps_[animationPhase];
                break;
            case Direction::UP:
                pixmap = &upPixmaps_[animationPhase];
                break;
            default:
                throw std::runtime_error("Cannot draw Ghost, wrong direction");
        }
    }
    else if(scaredState_ == ScaredState::SCARED_BLUE)
    {
        pixmap = scaredBluePixmaps_[animationPhase].get();
    }
    else if(scaredState_ == ScaredState::SCARED_WHITE)
    {
        pixmap = scaredWhitePixmaps_[animationPhase].get();
    }
    else
    {
        throw std::runtime_error("Cannot draw Ghost, wrong scared state");
    }

    painter->drawPixmap(rect_.toRect(), *pixmap);
}

void AbstractGhost::loadPixmaps(const std::array<QString, 8>& imagesUrls)
{
    const std::vector<PixmapLoader::PixmapEntry> pixmapEntries{{&leftPixmaps_[0],  imagesUrls.at(0)},
                                                               {&leftPixmaps_[1],  imagesUrls.at(1)},

                                                               {&rightPixmaps_[0], imagesUrls.at(2)},
                                                               {&rightPixmaps_[1], imagesUrls.at(3)},

                                                               {&upPixmaps_[0],    imagesUrls.at(4)},
                                                               {&upPixmaps_[1],    imagesUrls.at(5)},

                                                               {&downPixmaps_[0],  imagesUrls.at(6)},
                                                               {&downPixmaps_[1],  imagesUrls.at(7)}};

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

void AbstractGhost::initializeCommonPixmaps()
{
    //    scaredBluePixmaps_[2];
    //    scaredWhitePixmaps_[2];

    scaredBluePixmaps_[0] = std::make_unique<QPixmap>();
    scaredBluePixmaps_[1] = std::make_unique<QPixmap>();
    scaredWhitePixmaps_[0] = std::make_unique<QPixmap>();
    scaredWhitePixmaps_[1] = std::make_unique<QPixmap>();

    //    scaredBlue1Pixmap_ = std::make_unique<QPixmap>();
    //    scaredBlue2Pixmap_ = std::make_unique<QPixmap>();
    //    scaredWhite1Pixmap_ = std::make_unique<QPixmap>();
    //    scaredWhite2Pixmap_ = std::make_unique<QPixmap>();

    //    const std::vector<PixmapLoader::PixmapEntry> pixmapEntries = {{scaredBlue1Pixmap_.get(),  ":/ghosts/scared_blue/ghost_scared_blue_1.png"},
    //                                                                  {scaredBlue2Pixmap_.get(),  ":/ghosts/scared_blue/ghost_scared_blue_2.png"},
    //                                                                  {scaredWhite1Pixmap_.get(), ":/ghosts/scared_white/ghost_scared_white_1.png"},
    //                                                                  {scaredWhite2Pixmap_.get(), ":/ghosts/scared_white/ghost_scared_white_2.png"}};

    const std::vector<PixmapLoader::PixmapEntry> pixmapEntries = {{scaredBluePixmaps_[0].get(),  ":/ghosts/scared_blue/ghost_scared_blue_1.png"},
                                                                  {scaredBluePixmaps_[1].get(),  ":/ghosts/scared_blue/ghost_scared_blue_2.png"},
                                                                  {scaredWhitePixmaps_[0].get(), ":/ghosts/scared_white/ghost_scared_white_1.png"},
                                                                  {scaredWhitePixmaps_[1].get(), ":/ghosts/scared_white/ghost_scared_white_2.png"}};


    PixmapLoader::loadPixmaps(pixmapEntries);
}
