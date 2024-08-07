#include "game_manager.h"
#include "spdlog/spdlog.h"
#include "model/model.h"
#include "game_loop.h"

GameManager::GameManager(Model& model) : model_(model)
{
    gameState_ = GameState::READY_TO_START;
}

void GameManager::processStartOrRestartGameRequest()
{
    spdlog::debug("Processing start or restart game request");

    if(gameState_ == GameState::READY_TO_START)
    {
        startGame();
    }
    else if(gameState_ == GameState::STOPPED)
    {
        prepareGameToStart();
    }
    else
    {
        spdlog::debug("Game is not in READY_TO_START state. Start or restart game request rejected");
    }
}

void GameManager::prepareGameToStart()
{
    spdlog::debug("Prepare game to start");
    model_.reset();

    model_.getPacman().show();
    model_.getBlueGhost().show();
    model_.getOrangeGhost().show();
    model_.getPurpleGhost().show();
    model_.getRedGhost().show();

    model_.getScoreDisplay()->show();

    model_.getPelletsManager().showAllPellets();

    model_.getWhatToDrawManager()->drawBackground_ = true;
    model_.getWhatToDrawManager()->drawFPSCounter_ = true;

    gameState_ = GameState::READY_TO_START;

    model_.getScene()->invalidate();
}

void GameManager::endGame(GameResult gameResult)
{
    gameState_ = GameState::STOPPED;

    model_.getPacman().hide();
    model_.getBlueGhost().hide();
    model_.getOrangeGhost().hide();
    model_.getPurpleGhost().hide();
    model_.getRedGhost().hide();

    model_.getScoreDisplay()->hide();

    model_.getPelletsManager().hideAllPellets();

    gameResult_ = gameResult;
    gameLoop_->stop();

    model_.getWhatToDrawManager()->drawBackground_ = false;

    model_.getScene()->invalidate();
}

void GameManager::startGame()
{
    spdlog::debug("Starting game");

    gameState_ = GameState::RUNNING;

    gameLoop_->start();

    model_.getScene()->invalidate();
}
