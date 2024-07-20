#include "model/game_state_manager.h"

GameStateManager::GameStateManager() : state_(State::BEFORE_FIRST_RUN)
{
    shouldDrawBackground_ = true;
}

void GameStateManager::startGame()
{
    state_ = State::RUNNING;
    shouldDrawBackground_ = true;
}

void GameStateManager::endGame()
{
    shouldDrawBackground_ = false;
    state_ = State::STOPPED;
}

bool GameStateManager::isRunning() const
{
    return state_ == State::RUNNING;
}

bool GameStateManager::isPaused() const
{
    return state_ == State::PAUSED;
}

bool GameStateManager::isBeforeFirstRun() const
{
    return state_ == State::BEFORE_FIRST_RUN;
}

bool GameStateManager::isStopped() const
{
    return state_ == State::STOPPED;
}

void GameStateManager::togglePause()
{
    if(state_ == State::PAUSED)
    {
        state_ = State::RUNNING;
    }
    else if(state_ == State::RUNNING)
    {
        state_ = State::PAUSED;
    }
}

const bool& GameStateManager::getShouldDrawBackground() const
{
    return shouldDrawBackground_;

    //    if(gameStateManager_->isStopped())
    //    {
    //        shouldDrawBackground_ = false;
    ////        return false;
    //    }
    //    else
    //    {
    //        shouldDrawBackground_ = true;
    ////        return true;
    //    }
}
