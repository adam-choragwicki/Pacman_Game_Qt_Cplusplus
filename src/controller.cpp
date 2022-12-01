#include "controller.h"
#include "log_manager.h"
#include "collision_manager.h"

Controller::Controller(Model* model, MainWindow* view)
{
    model_ = model;
    view_ = view;

    //todo should it be here?
    frontendUpdateTimer_.setInterval(FRONTEND_UPDATE_FREQUENCY);
    frontendUpdateTimer_.start();

    subscribeToKeyEvents();

    connect(&model_->getPacman().getMovementTimer(), &QTimer::timeout, this, &Controller::pacmanMovementHandler);

    connect(&model_->getBlueGhost().getMovementTimer(), &QTimer::timeout, this, [this]()
    {
        ghostMovementHandler(&model_->getBlueGhost());
    });

    connect(&model_->getOrangeGhost().getMovementTimer(), &QTimer::timeout, this, [this]()
    {
        ghostMovementHandler(&model_->getOrangeGhost());
    });

    connect(&model_->getPurpleGhost().getMovementTimer(), &QTimer::timeout, this, [this]()
    {
        ghostMovementHandler(&model_->getPurpleGhost());
    });

    connect(&model_->getRedGhost().getMovementTimer(), &QTimer::timeout, this, [this]()
    {
        ghostMovementHandler(&model_->getRedGhost());
    });

    connect(&frontendUpdateTimer_, &QTimer::timeout, this, &Controller::frontendUpdateHandler);
}

void Controller::subscribeToKeyEvents()
{
    connect(view_, &MainWindow::keyPressedEvent, this, &Controller::processKeyPressedEvent);
}

void Controller::processKeyPressedEvent(Key key)
{
    GameState gameState = model_->getGameState();

    if(gameState == GameState::RUNNING)
    {
        Pacman& pacman = model_->getPacman();

        if(key == Key::LEFT)
        {
            pacman.setNextDirection(Direction::LEFT);
        }
        else if(key == Key::RIGHT)
        {
            pacman.setNextDirection(Direction::RIGHT);
        }
        else if(key == Key::UP)
        {
            pacman.setNextDirection(Direction::UP);
        }
        else if(key == Key::DOWN)
        {
            pacman.setNextDirection(Direction::DOWN);
        }
        else if(key == Key::PAUSE)
        {
            togglePause();
        }
    }
    else if(gameState == GameState::BEFORE_FIRST_RUN)
    {
        if(key == Key::SPACE)
        {
            startGame();
        }
    }
    else if(gameState == GameState::STOPPED)
    {
        if(key == Key::SPACE)
        {
            emit restartEvent();
        }
    }
    else if(gameState == GameState::PAUSED)
    {
        if(key == Key::PAUSE)
        {
            togglePause();
        }
    }
}

void Controller::startGame()
{
    model_->setGameState(GameState::RUNNING);

    for(MovableCharacter* movableCharacter : model_->getMovableCharacters())
    {
        movableCharacter->startMovement();
    }

    model_->getScoreManager().resetScore();
}

void Controller::endGame(GameResult gameResult)
{
    model_->setGameState(GameState::STOPPED);

    for(MovableCharacter* movableCharacter : model_->getMovableCharacters())
    {
        movableCharacter->stopMovement();
        movableCharacter->reset();
    }

    model_->getScreenTextManager().setGameResult(gameResult);
}

void Controller::togglePause()
{
    GameState gameState = model_->getGameState();

    if(gameState == GameState::RUNNING)
    {
        for(MovableCharacter* movableCharacter : model_->getMovableCharacters())
        {
            movableCharacter->stopMovement();
        }

        model_->setGameState(GameState::PAUSED);
    }
    else if(gameState == GameState::PAUSED)
    {
        for(MovableCharacter* movableCharacter : model_->getMovableCharacters())
        {
            movableCharacter->startMovement();
        }

        model_->setGameState(GameState::RUNNING);
    }
}

void Controller::frontendUpdateHandler()
{
    view_->update();
}

void Controller::pacmanMovementHandler()
{
    model_->getPacman().move();

    if(CollisionManager::checkAndProcessCollisionWithFoodball(model_->getPacman().getCoordinates(), model_->getBallItemsManager().getFoodballs()))
    {
        model_->getScoreManager().rewardPlayerForEatingFoodball();
    }

    if(CollisionManager::checkAndProcessCollisionWithPowerball(model_->getPacman().getCoordinates(), model_->getBallItemsManager().getPowerballs()))
    {
        model_->getScoreManager().rewardPlayerForEatingPowerball();

        for(AbstractGhost* ghost : model_->getGhosts())
        {
            ghost->scare();
        }
    }

    if(model_->getGameState() == GameState::RUNNING && model_->getBallItemsManager().getRemainingFoodballsCount() == 0)
    {
        endGame(GameResult::WIN);
    }
}

void Controller::ghostMovementHandler(AbstractGhost* ghost)
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
        const Coordinates& pacmanCoordinates = model_->getPacman().getCoordinates();

        ghost->move(Coordinates{pacmanCoordinates.x_, pacmanCoordinates.y_});

        const Coordinates& ghostCoordinates = ghost->getCoordinates();

        if(CollisionManager::checkCollisionWithGhost(pacmanCoordinates, ghostCoordinates))
        {
            if((ghost->getScaredState() == AbstractGhost::ScaredState::NO_SCARED))
            {
                endGame(GameResult::LOST);
            }
            else
            {
                model_->getScoreManager().rewardPlayerForEatingGhost();
                ghost->reset();
            }
        }
    }
}
