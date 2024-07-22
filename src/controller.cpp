#include "controller.h"
#include "input_handler.h"
#include "spdlog/spdlog.h"
#include <QKeyEvent>

Controller::Controller(Model& model, MainWindow& view) : model_(model), view_(view)
{
    spdlog::debug("Initializing controller");

    inputHandler_ = new InputHandler(model_);
    gameLoop_ = new GameLoop(model_);
    gameStateManager_ = new GameStateManager(model_);

    gameStateManager_->setGameLoop(gameLoop_);

    connect(gameLoop_, &GameLoop::endGame, gameStateManager_, &GameStateManager::endGame);

    model_.getScreenTextDisplay()->setGameStateManager(gameStateManager_);

    subscribeToKeyEvents();
    initializeFrontendEvents();
}

void Controller::subscribeToKeyEvents()
{
    connect(&view_, &MainWindow::keyPressedEvent, inputHandler_, &InputHandler::processKeyPressedEvent);

    connect(inputHandler_, &InputHandler::startOrRestartGameRequested, gameStateManager_, &GameStateManager::processStartOrRestartGameRequest);
    connect(inputHandler_, &InputHandler::togglePauseRequested, gameStateManager_, &GameStateManager::processTogglePauseRequest);
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
