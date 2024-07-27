#include "ghost_timing_manager.h"
#include "config.h"

GhostTimingManager::GhostTimingManager(const std::chrono::seconds& moveOutOfTheStartingBoxTimeout)
{
    initializeTimers(moveOutOfTheStartingBoxTimeout);
}

void GhostTimingManager::reset()
{
    timeToLeaveStartingBox_ = false;

    timeToLeaveStartingBoxTimer.stop();
    scaredBlueStateTimer_.stop();
    scaredWhiteStateTimer_.stop();
}

void GhostTimingManager::startLeaveStartingBoxTimer()
{
    timeToLeaveStartingBoxTimer.start();
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

void GhostTimingManager::initializeTimers(const std::chrono::seconds& moveOutOfTheStartingBoxTimeout)
{
    timeToLeaveStartingBoxTimer.setSingleShot(true);
    timeToLeaveStartingBoxTimer.setTimerType(Qt::PreciseTimer);
    timeToLeaveStartingBoxTimer.setInterval(moveOutOfTheStartingBoxTimeout);

    timeToLeaveStartingBoxTimer.callOnTimeout([this]()
                                              {
                                                  timeToLeaveStartingBox_ = true;
                                              });

    scaredBlueStateTimer_.setSingleShot(true);
    scaredBlueStateTimer_.setTimerType(Qt::PreciseTimer);
    scaredBlueStateTimer_.setInterval(SCARED_BLUE_TIME);

    scaredWhiteStateTimer_.setSingleShot(true);
    scaredWhiteStateTimer_.setTimerType(Qt::PreciseTimer);
    scaredWhiteStateTimer_.setInterval(SCARED_WHITE_TIME);
}
