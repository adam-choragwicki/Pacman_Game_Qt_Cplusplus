#include "model/ghosts/abstract_ghost.h"
#include <QtGui/QPainter>
#include "model/ghost_timing_manager.h"

AbstractGhost::AbstractGhost(const Coordinates& coordinates, const Direction initialDirection, const std::chrono::seconds& moveOutOfTheStartingBoxTimeout, AbstractGhostPixmapProvider* pixmapProvider) :
        MovableCharacter(coordinates, initialDirection, ANIMATION_SPEED_FACTOR, ANIMATION_PHASES_COUNT), pixmapProvider_(pixmapProvider)
{
    ghostTimingManager_ = std::make_unique<GhostTimingManager>(moveOutOfTheStartingBoxTimeout);

    MovableCharacter::reset();
    scaredState_ = ScaredState::NO_SCARED;
}

AbstractGhost::~AbstractGhost() = default;

void AbstractGhost::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    CustomGraphicsItem::paint(painter, option, widget);

    const QPixmap* pixmap;

    if(scaredState_ == ScaredState::NO_SCARED)
    {
        pixmap = &pixmapProvider_->getPixmap(direction_, animationPhase_);
    }
    else if(scaredState_ == ScaredState::SCARED_BLUE)
    {
        pixmap = &pixmapProvider_->getScaredBluePixmap(animationPhase_);
    }
    else if(scaredState_ == ScaredState::SCARED_WHITE)
    {
        pixmap = &pixmapProvider_->getScaredWhitePixmap(animationPhase_);
    }
    else
    {
        throw std::runtime_error("Cannot draw Ghost, wrong scared state");
    }

    drawPixmapAvoidingArtifacts(painter, pixmap);
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
