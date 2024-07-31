#include "controller.h"
#include "input_handler.h"
#include "spdlog/spdlog.h"
#include <QKeyEvent>

Controller::Controller(Model& model, MainWindow& view) : model_(model), view_(view)
{
    spdlog::debug("Initializing controller");

    inputHandler_ = std::make_unique<InputHandler>(model_);
    gameLoop_ = std::make_unique<GameLoop>(model_);
    gameManager_ = std::make_unique<GameManager>(model_);

    gameManager_->setGameLoop(gameLoop_.get());

    connect(gameLoop_.get(), &GameLoop::endGame, gameManager_.get(), &GameManager::endGame);

    model_.getScreenTextDisplay()->setGameManager(gameManager_.get());

    subscribeToKeyEvents();
    initializeFrontendEvents();

    gameManager_->prepareGameToStart();

    view_.getViewportUpdateTimer()->start();
}

void Controller::subscribeToKeyEvents()
{
    connect(&view_, &MainWindow::keyPressedEvent, inputHandler_.get(), &InputHandler::processKeyPressedEvent);

    connect(inputHandler_.get(), &InputHandler::startOrRestartGameRequested, gameManager_.get(), &GameManager::processStartOrRestartGameRequest);
}

void Controller::initializeFrontendEvents()
{
    connect(view_.getViewportUpdateTimer(), &QTimer::timeout, this, &Controller::viewportUpdateHandler);
}

void Controller::viewportUpdateHandler()
{
    QList<QRectF>& dirtyRegions = model_.getScene()->getDirtyRegions();

    if(!dirtyRegions.isEmpty())
    {
        view_.updateViewport(dirtyRegions);
        dirtyRegions.clear();
    }
}
