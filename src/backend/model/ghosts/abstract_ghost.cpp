#include "model/ghosts/abstract_ghost.h"
#include <QtGui/QPainter>
#include "model/ghost_timing_manager.h"
#include "pixmap_loader.h"
#include "pixmap_manager.h"

AbstractGhost::AbstractGhost(const Coordinates& coordinates, const Direction initialDirection, const std::chrono::seconds& moveOutOfTheStartingBoxTimeout, const std::array<QString, 6>& imagesUrls) :
        MovableCharacter(coordinates, initialDirection, ANIMATION_SPEED_FACTOR, ANIMATION_PHASES_COUNT)
{
    initializePixmaps(imagesUrls);

    ghostTimingManager_ = std::make_unique<GhostTimingManager>(moveOutOfTheStartingBoxTimeout);

    MovableCharacter::reset();
    scaredState_ = ScaredState::NO_SCARED;
}

AbstractGhost::~AbstractGhost() = default;

void AbstractGhost::initializePixmaps(const std::array<QString, 6>& imagesUrls)
{
    if(!commonPixmapsInitialized_)
    {
        initializeCommonPixmaps();
        commonPixmapsInitialized_ = true;
    }

    const std::vector<PixmapLoader::PixmapEntry> pixmapEntries{{&rightPixmaps_[0], imagesUrls.at(0)},
                                                               {&rightPixmaps_[1], imagesUrls.at(1)},

                                                               {&upPixmaps_[0],    imagesUrls.at(2)},
                                                               {&upPixmaps_[1],    imagesUrls.at(3)},

                                                               {&downPixmaps_[0],  imagesUrls.at(4)},
                                                               {&downPixmaps_[1],  imagesUrls.at(5)}};

    PixmapLoader::loadPixmaps(pixmapEntries);

    for(int i = 0; i < ANIMATION_PHASES_COUNT; ++i)
    {
        rightPixmaps_[i] = PixmapManager::scalePixmap(&rightPixmaps_[i], rect_);
        upPixmaps_[i] = PixmapManager::scalePixmap(&upPixmaps_[i], rect_);
        downPixmaps_[i] = PixmapManager::scalePixmap(&downPixmaps_[i], rect_);

        /* Mirror right pixmap horizontally to obtain left pixmap */
        leftPixmaps_[i] = PixmapManager::mirrorPixmapHorizontally(&rightPixmaps_[i]);
    }
}

void AbstractGhost::reset()
{
    MovableCharacter::reset();
    ghostTimingManager_->reset();
    scaredState_ = ScaredState::NO_SCARED;
    isSlowedDown_ = false;
}

void AbstractGhost::respawn()
{
    reset();
    ghostTimingManager_->setTimeToLeaveStartingBox();
}

bool AbstractGhost::isScared() const
{
    return scaredState_ != ScaredState::NO_SCARED;
}

void AbstractGhost::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    CustomGraphicsItem::paint(painter, option, widget);

    QPixmap* pixmap;
    const int animationPhase = animationPhase_ % 2;

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

    drawPixmapAvoidingArtifacts(painter, pixmap);
}

void AbstractGhost::setScared()
{
    scaredState_ = ScaredState::SCARED_BLUE;
    isSlowedDown_ = true;

    connect(&ghostTimingManager_->getScaredBlueStateTimer(), &QTimer::timeout, [this]()
    {
        scaredState_ = ScaredState::SCARED_WHITE;

        connect(&ghostTimingManager_->getScaredWhiteStateTimer(), &QTimer::timeout, [this]()
        {
            scaredState_ = ScaredState::NO_SCARED;
            isSlowedDown_ = false;
        });

        ghostTimingManager_->startScaredWhiteTimer();
    });

    ghostTimingManager_->startScaredBlueTimer();
}

void AbstractGhost::initializeCommonPixmaps()
{
    scaredBluePixmaps_[0] = std::make_unique<QPixmap>();
    scaredBluePixmaps_[1] = std::make_unique<QPixmap>();
    scaredWhitePixmaps_[0] = std::make_unique<QPixmap>();
    scaredWhitePixmaps_[1] = std::make_unique<QPixmap>();

    const std::vector<PixmapLoader::PixmapEntry> pixmapEntries = {{scaredBluePixmaps_[0].get(),  ":/ghosts/scared_blue/ghost_scared_blue_1.png"},
                                                                  {scaredBluePixmaps_[1].get(),  ":/ghosts/scared_blue/ghost_scared_blue_2.png"},
                                                                  {scaredWhitePixmaps_[0].get(), ":/ghosts/scared_white/ghost_scared_white_1.png"},
                                                                  {scaredWhitePixmaps_[1].get(), ":/ghosts/scared_white/ghost_scared_white_2.png"}};

    PixmapLoader::loadPixmaps(pixmapEntries);
}
