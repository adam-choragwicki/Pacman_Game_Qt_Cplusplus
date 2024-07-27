#include "model/ghosts/abstract_ghost.h"
#include <QtGui/QPainter>
#include "config.h"
#include "model/ghost_timing_manager.h"
#include "pixmap_loader.h"

AbstractGhost::AbstractGhost(const Coordinates& coordinates, const Direction initialDirection, const std::chrono::seconds& moveOutOfTheStartingBoxTimeout, const std::array<QString, 8>& imagesUrls) : MovableCharacter(coordinates, initialDirection)
{
    initializePixmaps(imagesUrls);

    ghostTimingManager_ = std::make_unique<GhostTimingManager>(moveOutOfTheStartingBoxTimeout);

    MovableCharacter::reset();
    scaredState_ = ScaredState::NO_SCARED;
}

AbstractGhost::~AbstractGhost() = default;

void AbstractGhost::initializePixmaps(const std::array<QString, 8>& imagesUrls)
{
    if(!commonPixmapsInitialized_)
    {
        initializeCommonPixmaps();
        commonPixmapsInitialized_ = true;
    }

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

void AbstractGhost::advanceAnimation()
{
    ++stepCounter_;

    if(stepCounter_ >= ANIMATION_SPEED_FACTOR)
    {
        stepCounter_ = 0;

        if(animationPhaseAscending_)
        {
            ++animationPhase_;
            if(animationPhase_ == ANIMATION_PHASES_COUNT - 1)
            {
                animationPhaseAscending_ = false;
            }
        }
        else
        {
            --animationPhase_;
            if(animationPhase_ == 0)
            {
                animationPhaseAscending_ = true;
            }
        }
    }
}

void AbstractGhost::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    CustomGraphicsItem::paint(painter, option, widget);

    const QPixmap* pixmap{};
    const int animationPhase = animationPhase_ % 2;

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
