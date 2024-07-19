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
//        scene_(*model_.getScene())
//        movingObjects_(model_.getMovingObjects()),
//        character_(*model_.getCharacter()),
//        creatures_(model_.getCreatures()),
//        projectileManager_(*model_.getProjectileManager()),
//        worldMap_(model_.getWorldMap()),
//        worldBoundaries_(model_.getWorldBoundaries())
{
    gameLoopTimer_ = new QTimer;
    connect(gameLoopTimer_, &QTimer::timeout, this, &GameLoop::execute);

    ghosts_.at(0) = &blueGhost_;
    ghosts_.at(1) = &orangeGhost_;
    ghosts_.at(2) = &purpleGhost_;
    ghosts_.at(3) = &redGhost_;

    //    connect(&model_.getPacmanTimingManager().getMovementTimer(), &QTimer::timeout, this, &GameLoop::pacmanMovementHandler);
    //
    //    for(const auto& ghostAndTimingManagerPair : model_.getGhostToGhostTimingManagerMapping())
    //    {
    //        connect(&ghostAndTimingManagerPair.second->getMovementTimer(), &QTimer::timeout, this, [&]()
    //        {
    //            ghostMovementHandler(*ghostAndTimingManagerPair.first);
    //        });
    //    }
}

void GameLoop::start()
{
    gameLoopTimer_->start(Config::Timing::TICK_INTERVAL);
}

void GameLoop::execute()
{
    pacmanMovementHandler();

    ghostMovementHandler(blueGhost_);
    ghostMovementHandler(orangeGhost_);
    ghostMovementHandler(purpleGhost_);
    ghostMovementHandler(redGhost_);

    if(CollisionManager::checkAndProcessCollisionWithFoodball(pacman_.getRect(), model_.getBallItemsManager().getFoodballs()))
    {
        model_.getScoreManager().increaseScoreForEatingFoodball();
    }

    if(CollisionManager::checkAndProcessCollisionWithPowerball(pacman_.getRect(), model_.getBallItemsManager().getPowerballs()))
    {
        model_.getScoreManager().increaseScoreForEatingPowerball();

        for(AbstractGhost* ghost : model_.getGhosts())
        {
            ghost->setScaredBlueState();
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

//    if(CollisionManager::checkCollisionWithGhost(pacman_.getRect(), blueGhost_.getRect()))
//    {
//        if(!blueGhost_.isScared())
//        {
//            model_.endGame(GameResult::LOST);
//        }
//        else
//        {
//            model_.getScoreManager().increaseScoreForEatingGhost();
//            blueGhost_.reset();
//            model_.getGhostToGhostTimingManagerMapping().at(&blueGhost_)->reset();
//        }
//    }




//
//    if(CollisionManager::checkCollisionWithGhost(pacman_.getRect(), ghost.getRect()))
//    {
//        if(!ghost.isScared())
//        {
//            model_.endGame(GameResult::LOST);
//        }
//        else
//        {
//            model_.getScoreManager().increaseScoreForEatingGhost();
//            ghost.reset();
//            model_.getGhostToGhostTimingManagerMapping().at(&ghost)->reset();
//        }
//    }


    if(gameStateManager_.isRunning() && model_.getBallItemsManager().getRemainingFoodballsCount() == 0)
    {
        model_.endGame(GameResult::WIN);
    }
}

void GameLoop::pacmanMovementHandler()
{
    model_.getPacmanMovementManager().processMove(pacman_, model_.getPathPoints());
}

void GameLoop::ghostMovementHandler(AbstractGhost& ghost)
{
    //artificial slowdown of ghost
    const int TARGET_SKIPPED_MOVES = 0;

    if(ghost.getSkippedMoves() == TARGET_SKIPPED_MOVES)
    {
        ghost.resetSkippedMoves();

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

//            if(CollisionManager::checkCollisionWithGhost(pacman_.getRect(), ghost.getRect()))
//            {
//                if(!ghost.isScared())
//                {
//                    model_.endGame(GameResult::LOST);
//                }
//                else
//                {
//                    model_.getScoreManager().increaseScoreForEatingGhost();
//                    ghost.reset();
//                    model_.getGhostToGhostTimingManagerMapping().at(&ghost)->reset();
//                }
//            }
        }
    }
    else
    {
        ghost.incrementSkippedMoves();
    }
}
