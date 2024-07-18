#include "controller.h"
#include "collision_manager.h"
#include "config.h"
#include "movement_manager.h"
#include <QKeyEvent>

Controller::Controller(Model& model, MainWindow& view) : model_(model), view_(view)
{
    subscribeToKeyEvents();
    initializeFrontendEvents();

    connect(&model_.getPacmanTimingManager().getMovementTimer(), &QTimer::timeout, this, &Controller::pacmanMovementHandler);

    for(const auto& ghostAndTimingManagerPair : model_.getGhostToGhostTimingManagerMapping())
    {
        connect(&ghostAndTimingManagerPair.second->getMovementTimer(), &QTimer::timeout, this, [&]()
        {
            ghostMovementHandler(*ghostAndTimingManagerPair.first);
        });
    }
}

void Controller::subscribeToKeyEvents()
{
    connect(&view_, &MainWindow::keyPressedEvent, this, &Controller::processKeyPressedEvent);
}

void Controller::processKeyPressedEvent(QKeyEvent* keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_Left:
        case Qt::Key_A:
            if(model_.getGameStateManager().isRunning())
            {
                model_.getPacman().setNextDirection(Direction::LEFT);
            }
            break;

        case Qt::Key_Right:
        case Qt::Key_D:
            if(model_.getGameStateManager().isRunning())
            {
                model_.getPacman().setNextDirection(Direction::RIGHT);
            }
            break;

        case Qt::Key_Up:
        case Qt::Key_W:
            if(model_.getGameStateManager().isRunning())
            {
                model_.getPacman().setNextDirection(Direction::UP);
            }
            break;

        case Qt::Key_Down:
        case Qt::Key_S:
            if(model_.getGameStateManager().isRunning())
            {
                model_.getPacman().setNextDirection(Direction::DOWN);
            }
            break;

        case Qt::Key_P:
            togglePause();
            break;

        case Qt::Key_Space:
            if(model_.getGameStateManager().isBeforeFirstRun() || model_.getGameStateManager().isStopped())
            {
                startGame();
            }
            break;
    }
}

void Controller::startGame()
{
    if(!model_.getGameStateManager().isBeforeFirstRun())
    {
        model_.reset();
    }

    model_.getGameStateManager().startGame();

    startAllCharacters();

    model_.getScoreManager().resetScore();
}

void Controller::endGame(GameResult gameResult)
{
    model_.getGameStateManager().endGame();

    stopAllCharacters();

    model_.getScreenTextManager().setGameResult(gameResult);
}

void Controller::togglePause()
{
    if(model_.getGameStateManager().isRunning())
    {
        stopAllCharacters();
        model_.getGameStateManager().togglePause();
    }
    else if(model_.getGameStateManager().isPaused())
    {
        startAllCharacters();
        model_.getGameStateManager().togglePause();
    }
}

void Controller::viewportUpdateHandler()
{
    view_.updateViewport();
}

void Controller::pacmanMovementHandler()
{
    //    model_.getPacmanMovementManager().processMove(model_.getPacman(), model_.getPathPoints());
    //
    //    if(CollisionManager::checkAndProcessCollisionWithFoodball(model_.getPacman().getRect(), model_.getBallItemsManager().getFoodballs()))
    //    {
    //        model_.getScoreManager().increaseScoreForEatingFoodball();
    //    }
    //
    //    if(CollisionManager::checkAndProcessCollisionWithPowerball(model_.getPacman().getRect(), model_.getBallItemsManager().getPowerballs()))
    //    {
    //        model_.getScoreManager().increaseScoreForEatingPowerball();
    //
    //        for(AbstractGhost* ghost : model_.getGhosts())
    //        {
    //            ghost->setScaredBlueState();
    //        }
    //
    //        for(GhostTimingManager* ghostTimingManager : model_.getGhostsTimingManagersContainer())
    //        {
    //            ghostTimingManager->startScaredBlueTimer();
    //            ghostTimingManager->reduceSpeed();
    //        }
    //    }
    //
    //    if(model_.getGameStateManager().isRunning() && model_.getBallItemsManager().getRemainingFoodballsCount() == 0)
    //    {
    //        endGame(GameResult::WIN);
    //    }
}

void Controller::ghostMovementHandler(AbstractGhost& ghost)
{
    //    if(model_.getGhostMovementManager().isGhostInsideStartingBox(ghost))
    //    {
    //        if(model_.getGhostToGhostTimingManagerMapping().at(&ghost)->isItTimeToLeaveStartingBox())
    //        {
    //            model_.getGhostMovementManager().moveOutOfStartingBox(ghost);
    //        }
    //        else
    //        {
    //            model_.getGhostMovementManager().moveInsideStartingBox(ghost);
    //        }
    //    }
    //    else
    //    {
    //        model_.getGhostMovementManager().processMove(ghost, model_.getPacman().getCoordinates(), model_.getPathPoints());
    //
    //        if(CollisionManager::checkCollisionWithGhost(model_.getPacman().getRect(), ghost.getRect()))
    //        {
    //            if(!ghost.isScared())
    //            {
    //                endGame(GameResult::LOST);
    //            }
    //            else
    //            {
    //                model_.getScoreManager().increaseScoreForEatingGhost();
    //                ghost.reset();
    //                model_.getGhostToGhostTimingManagerMapping().at(&ghost)->reset();
    //            }
    //        }
    //    }
}

void Controller::startAllCharacters()
{
    for(TimingManager* timingManager : model_.getAllTimingManagersContainer())
    {
        timingManager->startMovement();
    }
}

void Controller::stopAllCharacters()
{
    for(TimingManager* timingManager : model_.getAllTimingManagersContainer())
    {
        timingManager->stopMovement();
    }
}

void Controller::initializeFrontendEvents()
{
    auto* viewportUpdateTimer = new QTimer(this);
    connect(viewportUpdateTimer, &QTimer::timeout, this, &Controller::viewportUpdateHandler);
    viewportUpdateTimer->start(Config::Timing::VIEWPORT_UPDATE_INTERVAL);
}
