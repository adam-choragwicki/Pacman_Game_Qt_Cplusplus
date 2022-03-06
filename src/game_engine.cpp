#include "game_engine.h"
#include "drawer.h"
#include "log_manager.h"

GameEngine::GameEngine()
{
    gameState_ = GameState::beforeFirstRun;

    drawGraphicsItems();
    populateMapWithBalls();

    gameTickTimer_.setInterval(gameTickFrequency_);
    sceneUpdateTimer_.setInterval(sceneUpdateFrequency_);

    sceneUpdateTimer_.start();

    connect(&gameTickTimer_, &QTimer::timeout, this, &GameEngine::gameTickHandler);
    connect(&sceneUpdateTimer_, &QTimer::timeout, this, &GameEngine::sceneUpdateHandler);
    connect(&pacman_.getMovementTimer(), &QTimer::timeout, this, &GameEngine::pacmanMovementHandler);
    connect(&ghostBlue_.getMovementTimer(), &QTimer::timeout, this, [this](){ghostMovementHandler(&ghostBlue_);});
    connect(&ghostOrange_.getMovementTimer(), &QTimer::timeout, this, [this](){ghostMovementHandler(&ghostOrange_);});
    connect(&ghostPurple_.getMovementTimer(), &QTimer::timeout, this, [this](){ghostMovementHandler(&ghostPurple_);});
    connect(&ghostRed_.getMovementTimer(), &QTimer::timeout, this, [this](){ghostMovementHandler(&ghostRed_);});
}

void GameEngine::drawGraphicsItems()
{
    Drawer::drawItem(&pacman_);
    Drawer::drawItem(&ghostRed_);
    Drawer::drawItem(&ghostPurple_);
    Drawer::drawItem(&ghostBlue_);
    Drawer::drawItem(&ghostOrange_);
    Drawer::drawItem(&screenTextDisplay_);
    Drawer::drawItem(&scoreDisplay_);
}

void GameEngine::populateMapWithBalls()
{
    const QVector<QPoint> powerballPositions = gameMap_.generatePowerballPositions();
    const QVector<QPoint> foodballPositions = gameMap_.generateFoodballPositions();

    for(auto& powerballPosition : powerballPositions)
    {
        powerballGraphicsItems_.push_back(std::make_unique<Powerball>(powerballPosition.x(),
                                                                      powerballPosition.y()));
    }

    for(auto& foodballPosition : foodballPositions)
    {
        foodballGraphicsItems_.push_back(std::make_unique<Foodball>(foodballPosition.x(),
                                                                    foodballPosition.y()));
    }

    for(auto& powerballGraphicalItem : powerballGraphicsItems_)
    {
        Drawer::drawItem(powerballGraphicalItem.get());
    }

    for(auto& foodballGraphicalItem : foodballGraphicsItems_)
    {
        Drawer::drawItem(foodballGraphicalItem.get());
    }
}

void GameEngine::startGame()
{
    if(gameState_ != GameState::beforeFirstRun)
    {
        populateMapWithBalls();
    }

    scoreDisplay_.resetScore();
    screenTextDisplay_.hide();

    showGraphicsItems();

    for(MovableCharacterInterface* movableCharacter : movableCharacters)
    {
        movableCharacter->startMovement();
    }

    gameTickTimer_.start();
    gameState_ = GameState::gameRunning;
}

void GameEngine::endGame(GameResult gameResult)
{
    gameTickTimer_.stop();

    gameState_ = GameState::gameStopped;

    removeBalls();

    hideGraphicsItems();

    for(MovableCharacterInterface* movableCharacter : movableCharacters)
    {
        movableCharacter->stopMovement();
        movableCharacter->reset();
    }

    screenTextDisplay_.setScore(scoreDisplay_.getScore());
    screenTextDisplay_.setGameResult(gameResult);
    screenTextDisplay_.show();

    Drawer::updateScene();
}

void GameEngine::removeBalls()
{
    foodballGraphicsItems_.clear();
    powerballGraphicsItems_.clear();
}

void GameEngine::showGraphicsItems()
{
    Drawer::setGameArenaVisibility(true);

    for(QGraphicsItem* graphicsItem : graphicsItems_)
    {
        graphicsItem->show();
    }
}

void GameEngine::hideGraphicsItems()
{
    Drawer::setGameArenaVisibility(false);

    for(QGraphicsItem* graphicsItem : graphicsItems_)
    {
        graphicsItem->hide();
    }
}

void GameEngine::checkAndProcessCollisionWithGhost()
{
    for(GhostBase* ghost : ghosts_)
    {
        if(pacman_.collidesWithItem(ghost))
        {
            if((ghost->getScaredState() == GhostBase::ScaredState::noScared))
            {
                endGame(GameResult::gameLost);
            }
            else
            {
                scoreDisplay_.rewardPlayerForEatingGhost();
                ghost->reset();
            }
        }
    }
}

void GameEngine::checkAndProcessCollisionWithFoodball()
{
    auto iter = std::begin(foodballGraphicsItems_);

    for(auto& foodballGraphicalItem : foodballGraphicsItems_)
    {
        if(pacman_.collidesWithItem(foodballGraphicalItem.get()))
        {
            foodballGraphicsItems_.erase(iter);
            scoreDisplay_.rewardPlayerForEatingFoodball();
            return;
        }

        ++iter;
    }
}

void GameEngine::checkAndProcessCollisionWithPowerball()
{
    auto iter = std::begin(powerballGraphicsItems_);

    for(auto& powerballGraphicalItem : powerballGraphicsItems_)
    {
        if(pacman_.collidesWithItem(powerballGraphicalItem.get()))
        {
            powerballGraphicsItems_.erase(iter);
            scoreDisplay_.rewardPlayerForEatingPowerball();

            for(GhostBase* ghost : ghosts_)
            {
                ghost->scare();
            }

            return;
        }

        ++iter;
    }
}

void GameEngine::togglePause()
{
    if(gameState_ == GameState::gameRunning)
    {
        gameTickTimer_.stop();

        for(MovableCharacterInterface* movableCharacter : movableCharacters)
        {
            movableCharacter->stopMovement();
        }

        gameState_ = GameState::gamePaused;
    }
    else if(gameState_ == GameState::gamePaused)
    {
        gameTickTimer_.start();

        for(MovableCharacterInterface* movableCharacter : movableCharacters)
        {
            movableCharacter->resumeMovement();
        }


        gameState_ = GameState::gameRunning;
    }
}

void GameEngine::gameTickHandler()
{
    checkAndProcessCollisionWithGhost();
    checkAndProcessCollisionWithFoodball();
    checkAndProcessCollisionWithPowerball();

    if(gameState_ == GameState::gameRunning && foodballGraphicsItems_.size() == 0)
    {
        endGame(GameResult::gameWin);
    }
}

void GameEngine::sceneUpdateHandler()
{
    Drawer::updateScene();
}

void GameEngine::pacmanMovementHandler()
{
    pacman_.move();
    pacman_.advanceAnimation();
}

void GameEngine::ghostMovementHandler(GhostBase* ghost)
{
    if(ghost->isInsideStartingBox())
    {
        if(ghost->isItTimeToLeaveStartingBox())
        {
            ghost->moveOutOfStartingBox();
        }
        else
        {
            ghost->moveInsideStartingBox();
        }
    }
    else
    {
        ghost->move(pacman_.getX(), pacman_.getY());
        ghost->advanceAnimation();
    }
}

void GameEngine::processKey(QString key)
{
    if(gameState_ == GameState::gameRunning)
    {
        if(key == "left")
        {
            pacman_.setNextDirection(Direction::left);
        }
        else if(key == "right")
        {
            pacman_.setNextDirection(Direction::right);
        }
        else if(key == "up")
        {
            pacman_.setNextDirection(Direction::up);
        }
        else if(key == "down")
        {
            pacman_.setNextDirection(Direction::down);
        }
        else if(key == "pause")
        {
            togglePause();
        }
    }
    else if(gameState_ == GameState::beforeFirstRun || gameState_ == GameState::gameStopped)
    {
        if(key == "space")
        {
            startGame();
        }
    }
    else if(gameState_ == GameState::gamePaused)
    {
        if(key == "pause")
        {
            togglePause();
        }
    }
}
