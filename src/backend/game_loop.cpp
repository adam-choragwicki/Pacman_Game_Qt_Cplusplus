#include "game_loop.h"
#include "model/model.h"

#include "collision_manager.h"

#include "score_manager.h"
#include "config.h"
#include <QTimer>

GameLoop::GameLoop(Model& model) :
        model_(model),
        pacman_(model_.getPacman()),
        blueGhost_(model_.getBlueGhost()),
        orangeGhost_(model_.getOrangeGhost()),
        purpleGhost_(model_.getPurpleGhost()),
        redGhost_(model_.getRedGhost()),
        gameStateManager_(model_.getGameStateManager()),
        ghostMovementManager_(model_.getGhostMovementManager())
{
    gameLoopTimer_ = new QTimer;
    connect(gameLoopTimer_, &QTimer::timeout, this, &GameLoop::execute);

    ghosts_.at(0) = &blueGhost_;
    ghosts_.at(1) = &orangeGhost_;
    ghosts_.at(2) = &purpleGhost_;
    ghosts_.at(3) = &redGhost_;
}

void GameLoop::start()
{
    gameLoopTimer_->start(Config::Timing::GAME_LOOP_INTERVAL);
}

void GameLoop::togglePause()
{
    gameStateManager_.togglePause();

    if(gameStateManager_.isRunning())
    {
        gameLoopTimer_->start();
    }
    else
    {
        gameLoopTimer_->stop();
    }
}

void GameLoop::execute()
{
    if(gameStateManager_.isRunning())
    {
        pacmanMovementHandler();

        ghostMovementHandler(blueGhost_);
        ghostMovementHandler(orangeGhost_);
        ghostMovementHandler(purpleGhost_);
        ghostMovementHandler(redGhost_);

        if(CollisionManager::checkAndProcessPacmanCollisionWithFoodball(pacman_.getRect(), model_.getBallItemsManager().getFoodballs()))
        {
            model_.getScoreManager().increaseScoreForEatingFoodball();
        }

        if(CollisionManager::checkAndProcessPacmanCollisionWithPowerball(pacman_.getRect(), model_.getBallItemsManager().getPowerballs()))
        {
            model_.getScoreManager().increaseScoreForEatingPowerball();

            for(AbstractGhost* ghost : ghosts_)
            {
                ghost->setScaredBlueState();
                ghost->setSlowedDown(true);
            }

            for(GhostTimingManager* ghostTimingManager : model_.getGhostsTimingManagersContainer())
            {
                ghostTimingManager->startScaredBlueTimer();
                ghostTimingManager->reduceSpeed();
            }
        }

        for(AbstractGhost* ghost : ghosts_)
        {
            if(CollisionManager::checkCollisionWithGhost(pacman_.getRect(), ghost->getRect()))
            {
                if(!ghost->isScared())
                {
                    model_.endGame(GameResult::LOST);
                }
                else
                {
                    model_.getScoreManager().increaseScoreForEatingGhost();
                    ghost->reset();
                    model_.getGhostToGhostTimingManagerMapping().at(ghost)->reset();
                }
            }
        }

        if(gameStateManager_.isRunning() && model_.getBallItemsManager().getRemainingFoodballsCount() == 0)
        {
            model_.endGame(GameResult::WIN);
        }
    }
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
            if(model_.getGhostToGhostTimingManagerMapping().at(&ghost)->isItTimeToLeaveStartingBox())
            {
                ghostMovementManager_.moveOutOfStartingBox(ghost);
            }
            else
            {
                ghostMovementManager_.moveInsideStartingBox(ghost);
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
