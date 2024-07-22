#include "model/game_state_manager.h"
#include "spdlog/spdlog.h"

#include "game_loop.h"

//BEFORE FIRST RUN

//What is displayed:
//Background
//Characters
//Balls
//Score display
//Screen text press space to start


//RUNNING

//What is displayed:
//Background
//Characters
//Balls
//Score display
//NO SCREEN TEXT

//PAUSED

//What is displayed:
//Background
//Characters
//Balls
//Score display
//Screen text PAUSED

//STOPPED

//What is displayed:
//NO BACKGROUND
//NO CHARACTERS
//NO BALLS
//NO SCORE DISPLAY
//Screen text Game over/Congratulations etc.

GameStateManager::GameStateManager() : state_(State::BEFORE_FIRST_RUN)
{
    shouldDrawBackground_ = true;
}

void GameStateManager::processStartGameRequest()
{
    spdlog::debug("Processing start game request");

    if(state_ == State::BEFORE_FIRST_RUN || state_ == State::STOPPED)
    {
        startGame();
    }
    else
    {
        spdlog::debug("Game is not in BEFORE_FIRST_RUN or STOPPED state. Start game request rejected");
    }
}

void GameStateManager::processTogglePauseRequest()
{
    spdlog::debug("Processing toggle pause request");

    if(state_ == State::PAUSED || state_ == State::RUNNING)
    {
        togglePause();
    }
    else
    {
        spdlog::debug("Game is not in PAUSED or RUNNING state. Toggle pause request rejected");
    }
}

void GameStateManager::startGame()
{
    spdlog::debug("Starting game");

    state_ = State::RUNNING;

    gameLoop_->start();

    shouldDrawBackground_ = true;
}

void GameStateManager::togglePause()
{
    spdlog::debug("Toggling pause");

    if(state_ == State::PAUSED)
    {
        state_ = State::RUNNING;
        gameLoop_->start();
    }
    else if(state_ == State::RUNNING)
    {
        state_ = State::PAUSED;
        gameLoop_->stop();
    }
    else
    {
        spdlog::debug("Game is not in PAUSED or RUNNING state. Cannot toggle pause");
    }
}

void GameStateManager::endGame(GameResult gameResult)
{
    shouldDrawBackground_ = false;
    state_ = State::STOPPED;

    gameResult_ = gameResult;

    gameLoop_->stop();
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

void GameStateManager::transitionFromBeforeFirstRunToRunning()
{

}
