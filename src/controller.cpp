#include "controller.h"
#include "input_handler.h"
#include "spdlog/spdlog.h"
#include <QKeyEvent>

Controller::Controller(Model& model, MainWindow& view) : model_(model), view_(view)
{
    spdlog::debug("Initializing controller");

    inputHandler_ = new InputHandler(model_);
    gameLoop_ = new GameLoop(model_);

    model_.getGameStateManager().setGameLoop(gameLoop_);

    subscribeToKeyEvents();
    initializeFrontendEvents();
}

void Controller::subscribeToKeyEvents()
{
    connect(&view_, &MainWindow::keyPressedEvent, inputHandler_, &InputHandler::processKeyPressedEvent);

    connect(inputHandler_, &InputHandler::startGameRequested, &model_.getGameStateManager(), &GameStateManager::processStartGameRequest);
    connect(inputHandler_, &InputHandler::togglePauseRequested, &model_.getGameStateManager(), &GameStateManager::processTogglePauseRequest);
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
