#include "controller.h"
#include "collision_manager.h"
#include "config.h"
#include "abstract_movement_manager.h"
#include "input_handler.h"
#include "game_loop.h"
#include "score_manager.h"
#include <QKeyEvent>

Controller::Controller(Model& model, MainWindow& view) : model_(model), view_(view)
{
    inputHandler_ = new InputHandler(model_);
    gameLoop_ = new GameLoop(model_);

    subscribeToKeyEvents();
    initializeFrontendEvents();

    //    connect(&model_.getPacmanTimingManager().getMovementTimer(), &QTimer::timeout, this, &Controller::pacmanMovementHandler);
    //
    //    for(const auto& ghostAndTimingManagerPair : model_.getGhostToGhostTimingManagerMapping())
    //    {
    //        connect(&ghostAndTimingManagerPair.second->getMovementTimer(), &QTimer::timeout, this, [&]()
    //        {
    //            ghostMovementHandler(*ghostAndTimingManagerPair.first);
    //        });
    //    }

    //    gameLoop_->start();
}

void Controller::subscribeToKeyEvents()
{
    connect(&view_, &MainWindow::keyPressedEvent, inputHandler_, &InputHandler::processKeyPressedEvent);

    connect(inputHandler_, &InputHandler::startGameRequested, this, &Controller::startGame);
    connect(inputHandler_, &InputHandler::togglePauseRequested, gameLoop_, &GameLoop::togglePause);
}

void Controller::initializeFrontendEvents()
{
    auto* viewportUpdateTimer = new QTimer(this);
    connect(viewportUpdateTimer, &QTimer::timeout, this, &Controller::viewportUpdateHandler);
    viewportUpdateTimer->start(Config::Timing::VIEWPORT_UPDATE_INTERVAL);
}

void Controller::viewportUpdateHandler()
{
    view_.updateViewport();
}

void Controller::startGame()
{
    model_.startGame();

    gameLoop_->start();

    //    if(!model_.getGameStateManager().isBeforeFirstRun())
    //    {
    //        model_.reset();
    //    }
    //
    //    model_.getGameStateManager().startGame();
    //
    //    startAllCharacters();
    //
    //    model_.getScoreManager().resetScore();
}

void Controller::endGame(GameResult gameResult)
{
    model_.endGame(gameResult);

    //    model_.getGameStateManager().endGame();
    //
    //    stopAllCharacters();
    //
    //    model_.getScreenTextManager().setGameResult(gameResult);
}

//void Controller::togglePause()
//{
//    if(model_.getGameStateManager().isRunning())
//    {
//        stopAllCharacters();
//        model_.getGameStateManager().togglePause();
//    }
//    else if(model_.getGameStateManager().isPaused())
//    {
//        startAllCharacters();
//        model_.getGameStateManager().togglePause();
//    }
//}
