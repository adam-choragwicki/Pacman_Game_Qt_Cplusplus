#include "controller.h"
#include "collision_manager.h"
#include "config.h"
#include "abstract_movement_manager.h"
#include "input_handler.h"
#include "game_loop.h"
#include "spdlog/spdlog.h"
#include <QKeyEvent>

Controller::Controller(Model& model, MainWindow& view) : model_(model), view_(view)
{
    spdlog::debug("Initializing controller");

    inputHandler_ = new InputHandler(model_);
    gameLoop_ = new GameLoop(model_);

    subscribeToKeyEvents();
    initializeFrontendEvents();
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
    if(model_.getGameStateManager().isBeforeFirstRun() || model_.getGameStateManager().isStopped())
    {
        model_.startGame();
        gameLoop_->start();
    }

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
