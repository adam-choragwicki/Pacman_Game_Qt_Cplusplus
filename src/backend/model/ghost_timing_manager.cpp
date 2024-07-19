#include "ghost_timing_manager.h"

GhostTimingManager::GhostTimingManager(AbstractGhost& abstractGhost, std::chrono::seconds startTimeout) : ghost_(abstractGhost)
{
    leaveStartingBoxTimer.setSingleShot(true);
    leaveStartingBoxTimer.setInterval(startTimeout);

    scaredBlueStateTimer_.setSingleShot(true);
    scaredBlueStateTimer_.setInterval(Config::Timing::Ghost::SCARED_BLUE_TIME);

    scaredWhiteStateTimer_.setSingleShot(true);
    scaredWhiteStateTimer_.setInterval(Config::Timing::Ghost::SCARED_WHITE_TIME);

    leaveStartingBoxTimer.callOnTimeout(this, &GhostTimingManager::setLeaveStartingBox);

    connect(&scaredBlueStateTimer_, &QTimer::timeout, this, &GhostTimingManager::changeToScaredWhite);
    connect(&scaredWhiteStateTimer_, &QTimer::timeout, this, &GhostTimingManager::changeToNoScared);
}

void GhostTimingManager::reset()
{
    timeToLeaveStartingBox_ = false;
    leaveStartingBoxTimer.start();

    scaredBlueStateTimer_.stop();
    scaredWhiteStateTimer_.stop();
}

void GhostTimingManager::startMovement()
{
    leaveStartingBoxTimer.start();
}

void GhostTimingManager::stopMovement()
{
}

void GhostTimingManager::reduceSpeed()
{
}

void GhostTimingManager::resetSpeed()
{
}

void GhostTimingManager::startScaredBlueTimer()
{
    scaredWhiteStateTimer_.stop();
    scaredBlueStateTimer_.start();
}

void GhostTimingManager::startScaredWhiteTimer()
{
    scaredBlueStateTimer_.stop();
    scaredWhiteStateTimer_.start();
}

void GhostTimingManager::setLeaveStartingBox()
{
    timeToLeaveStartingBox_ = true;
}

void GhostTimingManager::changeToScaredWhite()
{
    ghost_.setScaredWhiteState();
    startScaredWhiteTimer();
}

void GhostTimingManager::changeToNoScared()
{
    ghost_.resetScaredState();
    ghost_.setSlowedDown(false);
    resetSpeed();
}
