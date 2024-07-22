#include "game_loop.h"
#include "model/model.h"
#include "collision_manager.h"
#include "config.h"
#include "model/ghost_timing_manager.h"
#include <QTimer>

GameLoop::GameLoop(Model& model) :
        model_(model),
        pacman_(model_.getPacman()),
        blueGhost_(model_.getBlueGhost()),
        orangeGhost_(model_.getOrangeGhost()),
        purpleGhost_(model_.getPurpleGhost()),
        redGhost_(model_.getRedGhost()),
        ghostMovementManager_(model_.getGhostMovementManager()),
        scoreManager_(model_.getScoreManager()),
        ballItemsManager_(model_.getBallItemsManager())
{
    gameLoopTimer_ = new QTimer;
    connect(gameLoopTimer_, &QTimer::timeout, this, &GameLoop::execute);

    ghosts_.at(0) = &blueGhost_;
    ghosts_.at(1) = &orangeGhost_;
    ghosts_.at(2) = &purpleGhost_;
    ghosts_.at(3) = &redGhost_;

    firstStartInCurrentGame_ = true;
}

void GameLoop::start()
{
    if(firstStartInCurrentGame_)
    {
        for(AbstractGhost* ghost : ghosts_)
        {
            ghost->getGhostTimingManager()->startLeaveStartingBoxTimer();
        }

        firstStartInCurrentGame_ = false;
    }

    gameLoopTimer_->start(Config::Timing::GAME_LOOP_INTERVAL);
}

void GameLoop::stop()
{
    gameLoopTimer_->stop();
}

void GameLoop::execute()
{
    //    if(gameStateManager_.isRunning())
    //    {
    pacmanMovementHandler();

    ghostMovementHandler(blueGhost_);
    ghostMovementHandler(orangeGhost_);
    ghostMovementHandler(purpleGhost_);
    ghostMovementHandler(redGhost_);

    if(CollisionManager::checkAndProcessPacmanCollisionWithFoodball(pacman_.getRect(), ballItemsManager_.getFoodballs()))
    {
        scoreManager_.increaseScoreForEatingFoodball();
    }

    if(CollisionManager::checkAndProcessPacmanCollisionWithPowerball(pacman_.getRect(), ballItemsManager_.getPowerballs()))
    {
        scoreManager_.increaseScoreForEatingPowerball();

        for(AbstractGhost* ghost : ghosts_)
        {
            ghost->setScared();
        }
    }

    for(AbstractGhost* ghost : ghosts_)
    {
        if(CollisionManager::checkAndProcessPacmanCollisionWithGhost(pacman_.getRect(), ghost->getRect()))
        {
            if(!ghost->isScared())
            {
                emit endGame(GameResult::LOST);
            }
            else
            {
                scoreManager_.increaseScoreForEatingGhost();
                ghost->reset();
            }
        }
    }

    if(ballItemsManager_.getRemainingFoodballsCount() == 0)
        //        if(gameStateManager_.isRunning() && ballItemsManager_.getRemainingFoodballsCount() == 0)
    {
        emit endGame(GameResult::WIN);
    }
    //    }
}

void GameLoop::pacmanMovementHandler()
{
    model_.getPacmanMovementManager().processMove(pacman_, model_.getPathPoints());
    pacman_.advanceAnimation();
}

void GameLoop::ghostMovementHandler(AbstractGhost& ghost)
{
    static int turnsCounter = 0;

    static const int SKIP_TURNS = 5;
    bool canMoveThisTurn{};

    //artificial slowdown of ghost
    if(ghost.isSlowedDown())
    {
        if(turnsCounter % SKIP_TURNS == 0)
        {
            canMoveThisTurn = true;
        }
    }
    else
    {
        canMoveThisTurn = true;
    }

    if(canMoveThisTurn)
    {
        if(ghostMovementManager_.isGhostInsideStartingBox(ghost))
        {
            if(ghost.getGhostTimingManager()->isItTimeToLeaveStartingBox())
            {
                ghostMovementManager_.moveOutOfStartingBox(ghost);
            }
            else
            {
                ghostMovementManager_.moveUpAndDownInsideStartingBox(ghost);
            }
        }
        else
        {
            ghostMovementManager_.processMove(ghost, pacman_.getCoordinates(), model_.getPathPoints());
        }

        ghost.advanceAnimation();
    }

    ++turnsCounter;
}
