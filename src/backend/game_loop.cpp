#include "game_loop.h"
#include "model/model.h"

#include "collision_manager.h"
//#include "moving_objects_collision_resolver.h"
//#include "model/physics_manager.h"
//#include "model/items/abstract_projectile.h"

#include <QTimer>

GameLoop::GameLoop(Model& model) :
        model_(model),
        scene_(*model_.getScene())
//        movingObjects_(model_.getMovingObjects()),
//        character_(*model_.getCharacter()),
//        creatures_(model_.getCreatures()),
//        projectileManager_(*model_.getProjectileManager()),
//        worldMap_(model_.getWorldMap()),
//        worldBoundaries_(model_.getWorldBoundaries())
{
    gameLoopTimer_ = new QTimer;
    connect(gameLoopTimer_, &QTimer::timeout, this, &GameLoop::execute);


}

void GameLoop::start()
{
    gameLoopTimer_->start(Config::Timing::TICK_INTERVAL);
}

void GameLoop::execute()
{
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
