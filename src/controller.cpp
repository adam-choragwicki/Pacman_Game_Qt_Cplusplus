#include "controller.h"
#include "input_handler.h"
#include "spdlog/spdlog.h"
#include <QKeyEvent>
#include <QElapsedTimer>

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

    connect(model_.getScene(), &QGraphicsScene::changed, this, &Controller::updateDirtyRegion);

    gameManager_->prepareGameToStart();
}

void Controller::subscribeToKeyEvents()
{
    connect(&view_, &MainWindow::keyPressedEvent, inputHandler_.get(), &InputHandler::processKeyPressedEvent);

    connect(inputHandler_.get(), &InputHandler::startOrRestartGameRequested, gameManager_.get(), &GameManager::processStartOrRestartGameRequest);
}

void Controller::initializeFrontendEvents()
{
    auto* viewportUpdateTimer = new QTimer(this);
    viewportUpdateTimer->setTimerType(Qt::PreciseTimer);
    connect(viewportUpdateTimer, &QTimer::timeout, this, &Controller::viewportUpdateHandler);
    viewportUpdateTimer->start(Config::Timing::VIEWPORT_UPDATE_INTERVAL);
}

//void Controller::viewportUpdateHandler()
//{
////    model_.getScene().chan
//
////    view_.updateViewport(dirtyRegion);
//}

void Controller::viewportUpdateHandler()
{
    if (!dirtyRegions_.isEmpty())
    {
        view_.updateViewport(dirtyRegions_);
        dirtyRegions_.clear();  // Clear the collected dirty regions after updating
    }
}
//
//void Controller::updateDirtyRegion(const QList<QRectF>& dirtyRegions)
//{
//    view_.updateViewport(dirtyRegions);
//}

void Controller::updateDirtyRegion(const QList<QRectF>& dirtyRegion)
{
    for (const QRectF& rect : dirtyRegion)
    {
        dirtyRegions_.append(rect);
    }
}
