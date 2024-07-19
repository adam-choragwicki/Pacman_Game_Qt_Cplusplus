#include "game_loop.h"
#include "model/model.h"

#include "collision_manager.h"

#include "score_manager.h"
#include "config.h"
#include <QTimer>

GameLoop::GameLoop(Model& model) :
        model_(model), blueGhost_(model_.getBlueGhost()), orangeGhost_(model_.getOrangeGhost()), purpleGhost_(model_.getPurpleGhost()), redGhost_(model_.getRedGhost()), ghostMovementManager_(model_.getGhostMovementManager())
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

    //    //resolve movable objects collisions start
    //    for(MovingObject* movingObject : movingObjects_)
    //    {
    //        if(!movingObject->getMovementVector().isZero())
    //        {
    //            MovementVector adjustedMovementVector = MovingObjectCollisionWithTileResolver::adjustMovementVector(*movingObject, worldMap_.getTiles(), worldBoundaries_);
    //
    //            //TODO isolate single collision and handle it
    //
    //            movingObject->setMovementVector(adjustedMovementVector);
    //            movingObject->move();
    //        }
    //    }
    //    //resolve movable objects collisions start
    //
    //    //creature shooting start
    //    //    for(AbstractCreature* creature : creatures)
    //    //    {
    //    //        if(creature->canFireAgain())
    //    //        {
    //    //            creature->shootAtCharacter(character.sceneBoundingRect().center(), projectileManager);
    //    //        }
    //    //    }
    //    //creature shooting end
    //
    //    if(character_.isHoldingRope())
    //    {
    //        //check if character still collides with rope
    //        RopeCollisionResult ropeCollisionResult = CollisionManager::checkCharacterCollisionWithRope(character_, &scene_);
    //
    //        if(ropeCollisionResult.isCollision_)
    //        {
    //            character_.setHoldingRope(true);
    //        }
    //        else
    //        {
    //            character_.setHoldingRope(false);
    //        }
    //    }
    //
    //    if(character_.isMoveUpRequested())
    //    {
    //        //check if character collides with rope
    //        RopeCollisionResult ropeCollisionResult = CollisionManager::checkCharacterCollisionWithRope(character_, &scene_);
    //
    //        if(ropeCollisionResult.isCollision_)
    //        {
    //            character_.setHoldingRope(true);
    //        }
    //        else
    //        {
    //            character_.setHoldingRope(false);
    //        }
    //    }
    //
    //    for(MovingObject* movingObject : movingObjects_)
    //    {
    //        movingObject->setOnStableGround(false);
    //    }
    //
    //    if(character_.isHoldingRope())
    //    {
    //        character_.setOnStableGround(true);
    //        PhysicsManager::applyRopeFriction(character_);
    //    }
    //
    //    for(MovingObject* movingObject : movingObjects_)
    //    {
    //        if((!movingObject->isRising()) && CollisionManager::isAnyStableGroundBelowMovingObject(*movingObject, &scene_))
    //        {
    //            //qDebug() << "Stable ground below character";
    //            movingObject->setOnStableGround(true);
    //        }
    //
    //        if(movingObject->isOnStableGround())
    //        {
    //            movingObject->setCanJumpAgain(true);
    //        }
    //        else
    //        {
    //            PhysicsManager::applyGravity(*movingObject);
    //        }
    //    }
    //
    //    if(character_.isMoveDownRequested())
    //    {
    //        dropDownCharacter();
    //    }
    //
    //    //    AiManager::generateNextMove(character, creature);
    //
    //
    //    //move projectiles start
    //    for(AbstractProjectile* projectile : projectileManager_.getProjectiles())
    //    {
    //        const MovementVector& projectileMovementVector = projectile->getMovementVector();
    //
    //        if(!projectileMovementVector.isZero())
    //        {
    //            projectile->move();
    //        }
    //    }
    //    //move projectiles end
    //
    //    projectileManager_.processProjectilesCollisions(character_, creatures_, worldMap_.getTiles(), worldBoundaries_);
    //
    //    PhysicsManager::applyAirFriction(character_);
}

void GameLoop::pacmanMovementHandler()
{
    model_.getPacmanMovementManager().processMove(model_.getPacman(), model_.getPathPoints());

    if(CollisionManager::checkAndProcessCollisionWithFoodball(model_.getPacman().getRect(), model_.getBallItemsManager().getFoodballs()))
    {
        model_.getScoreManager().increaseScoreForEatingFoodball();
    }

    if(CollisionManager::checkAndProcessCollisionWithPowerball(model_.getPacman().getRect(), model_.getBallItemsManager().getPowerballs()))
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

    if(model_.getGameStateManager().isRunning() && model_.getBallItemsManager().getRemainingFoodballsCount() == 0)
    {
        model_.endGame(GameResult::WIN);
    }
}

void GameLoop::ghostMovementHandler(AbstractGhost& ghost)
{
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
            ghostMovementManager_.processMove(ghost, model_.getPacman().getCoordinates(), model_.getPathPoints());

            if(CollisionManager::checkCollisionWithGhost(model_.getPacman().getRect(), ghost.getRect()))
            {
                if(!ghost.isScared())
                {
                    model_.endGame(GameResult::LOST);
                }
                else
                {
                    model_.getScoreManager().increaseScoreForEatingGhost();
                    ghost.reset();
                    model_.getGhostToGhostTimingManagerMapping().at(&ghost)->reset();
                }
            }
        }
    }
    else
    {
        ghost.incrementSkippedMoves();
    }
}
