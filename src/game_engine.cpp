#include "game_engine.h"
#include "drawer.h"

GameMap GameEngine::gameMap_;

GameEngine::GameEngine()
{
    movableCharacters = {&pacman_, &ghostBlue_, &ghostOrange_, &ghostPurple_, &ghostRed_};
    ghosts_ = {&ghostBlue_, &ghostOrange_, &ghostPurple_, &ghostRed_};
    graphicsItems_ = {&pacman_, &ghostBlue_, &ghostOrange_, &ghostPurple_, &ghostRed_, &scoreDisplay_};

    ballItemsManager_.populateMapWithBalls(gameMap_);

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

    if(gameState_ != GameState::beforeFirstRun)
    {
        startGame();
    }
}

GameEngine::~GameEngine()
{

}

void GameEngine::startGame()
{
    if(gameState_ != GameState::beforeFirstRun)
    {
        ballItemsManager_.populateMapWithBalls(gameMap_);
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

    ballItemsManager_.removeBalls();

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
    if(ballItemsManager_.checkAndProcessCollisionWithFoodball(pacman_))
    {
        scoreDisplay_.rewardPlayerForEatingFoodball();
    }
}

void GameEngine::checkAndProcessCollisionWithPowerball()
{
    if(ballItemsManager_.checkAndProcessCollisionWithPowerball(pacman_))
    {
        scoreDisplay_.rewardPlayerForEatingPowerball();

        for(GhostBase* ghost : ghosts_)
        {
            ghost->scare();
        }
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
            movableCharacter->startMovement();
        }

        gameState_ = GameState::gameRunning;
    }
}

void GameEngine::gameTickHandler()
{
    checkAndProcessCollisionWithGhost();
    checkAndProcessCollisionWithFoodball();
    checkAndProcessCollisionWithPowerball();

    if(gameState_ == GameState::gameRunning && ballItemsManager_.getRemainingFoodballsCount() == 0)
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
        ghost->move(Coordinates{pacman_.getCoordinates().x_, pacman_.getCoordinates().y_});
    }
}

void GameEngine::processKey(const Key key)
{
    if(gameState_ == GameState::gameRunning)
    {
        if(key == Key::left)
        {
            pacman_.setNextDirection(Direction::left);
        }
        else if(key == Key::right)
        {
            pacman_.setNextDirection(Direction::right);
        }
        else if(key == Key::up)
        {
            pacman_.setNextDirection(Direction::up);
        }
        else if(key == Key::down)
        {
            pacman_.setNextDirection(Direction::down);
        }
        else if(key == Key::pause)
        {
            togglePause();
        }
    }
    else if(gameState_ == GameState::beforeFirstRun)
    {
        if(key == Key::space)
        {
            startGame();
        }
    }
    else if(gameState_ == GameState::gameStopped)
    {
        if(key == Key::space)
        {
            emit restartGame();
        }
    }
    else if(gameState_ == GameState::gamePaused)
    {
        if(key == Key::pause)
        {
            togglePause();
        }
    }
}
