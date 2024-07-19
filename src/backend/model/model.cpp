#include "model.h"

#include "path_points.h"
#include "pacman.h"
#include "ball_items_manager.h"
#include "ghosts/red_ghost.h"
#include "ghosts/purple_ghost.h"
#include "ghosts/blue_ghost.h"
#include "ghosts/orange_ghost.h"

#include "score_manager.h"
#include "screen_text_manager.h"
#include "game_state_manager.h"
#include "abstract_timing_manager.h"
#include "abstract_movement_manager.h"

#include "pacman_movement_manager.h"
#include "ghost_movement_manager.h"

#include "balls/foodball.h"
#include "balls/powerball.h"
#include "screen_text_display.h"

#include "path_points.h"
#include "score_display.h"

#include <QtWidgets/QGraphicsScene>

Model::Model()
{
    initScene();

    scoreManager_ = new ScoreManager;

    scoreDisplay_ = new ScoreDisplay(*scoreManager_);

    screenTextManager_ = new ScreenTextManager;

    pathPoints_ = std::make_unique<PathPoints>();

    ballItemsManager_ = std::make_unique<BallItemsManager>(*pathPoints_);

    pacman_ = std::make_unique<Pacman>();
    blueGhost_ = std::make_unique<BlueGhost>();
    orangeGhost_ = std::make_unique<OrangeGhost>();
    purpleGhost_ = std::make_unique<PurpleGhost>();
    redGhost_ = std::make_unique<RedGhost>();

    gameStateManager_ = std::make_unique<GameStateManager>();

    pacmanTimingManager_ = std::make_unique<PacmanTimingManager>();
    blueGhostTimingManager_ = std::make_unique<GhostTimingManager>(*blueGhost_, Config::StartTimeout::BLUE_GHOST);
    orangeGhostTimingManager_ = std::make_unique<GhostTimingManager>(*orangeGhost_, Config::StartTimeout::ORANGE_GHOST);
    purpleGhostTimingManager_ = std::make_unique<GhostTimingManager>(*purpleGhost_, Config::StartTimeout::PURPLE_GHOST);
    redGhostTimingManager_ = std::make_unique<GhostTimingManager>(*redGhost_, Config::StartTimeout::RED_GHOST);

    ghostToGhostTimingManagerMapping_.insert_or_assign(blueGhost_.get(), blueGhostTimingManager_.get());
    ghostToGhostTimingManagerMapping_.insert_or_assign(orangeGhost_.get(), orangeGhostTimingManager_.get());
    ghostToGhostTimingManagerMapping_.insert_or_assign(purpleGhost_.get(), purpleGhostTimingManager_.get());
    ghostToGhostTimingManagerMapping_.insert_or_assign(redGhost_.get(), redGhostTimingManager_.get());

    pacmanMovementManager_ = std::make_unique<PacmanMovementManager>();
    ghostMovementManager_ = std::make_unique<GhostMovementManager>();

    screenTextDisplay_ = std::make_unique<ScreenTextDisplay>(*gameStateManager_, *screenTextManager_, *scoreManager_);

    groupObjectsIntoContainers();

    addItemsToScene();
}

void Model::groupObjectsIntoContainers()
{
    movableCharacters = {pacman_.get(), blueGhost_.get(), orangeGhost_.get(), purpleGhost_.get(), redGhost_.get()};

    ghosts_ = {blueGhost_.get(), orangeGhost_.get(), purpleGhost_.get(), redGhost_.get()};

    ghostTimingManagersContainer = {blueGhostTimingManager_.get(), orangeGhostTimingManager_.get(), purpleGhostTimingManager_.get(), redGhostTimingManager_.get()};
    allTimingManagersContainer = {pacmanTimingManager_.get(), blueGhostTimingManager_.get(), orangeGhostTimingManager_.get(), purpleGhostTimingManager_.get(), redGhostTimingManager_.get()};
}

void Model::reset()
{
    gameStateManager_ = std::make_unique<GameStateManager>();
    ballItemsManager_ = std::make_unique<BallItemsManager>(*pathPoints_);

    for(auto& movableCharacter : movableCharacters)
    {
        movableCharacter->reset();
    }

    for(auto& ghostTimingManager : ghostTimingManagersContainer)
    {
        ghostTimingManager->reset();
    }

    addItemsToScene();
}

void Model::initScene()
{
    scene_ = new QGraphicsScene();

    const int ARENA_WIDTH_PX = 614;
    const int ARENA_HEIGHT_PX = 730;

    scene_->setSceneRect(0, 0, ARENA_WIDTH_PX, ARENA_HEIGHT_PX);
}

void Model::addItemsToScene()
{
    scene_->addItem(pacman_.get());

    scene_->addItem(blueGhost_.get());
    scene_->addItem(orangeGhost_.get());
    scene_->addItem(purpleGhost_.get());
    scene_->addItem(redGhost_.get());

    scene_->addItem(screenTextDisplay_.get());

    addBallsToScene();

    scene_->addItem(scoreDisplay_);
}

//void Model::startGame()
//{
//    if(!model_.getGameStateManager().isBeforeFirstRun())
//    {
//        model_.reset();
//    }
//
//    model_.getGameStateManager().startGame();
//
//    startAllCharacters();
//
//    model_.getScoreManager().resetScore();
//}
//
//void Model::endGame(GameResult gameResult)
//{
//    model_.getGameStateManager().endGame();
//
//    stopAllCharacters();
//
//    model_.getScreenTextManager().setGameResult(gameResult);
//}

void Model::startGame()
{
    if(!getGameStateManager().isBeforeFirstRun())
    {
        reset();
    }

    getGameStateManager().startGame();

    startAllCharacters();

    getScoreManager().resetScore();
}

void Model::endGame(GameResult gameResult)
{
    getGameStateManager().endGame();

    stopAllCharacters();

    getScreenTextManager().setGameResult(gameResult);
}

//void Model::startAllCharacters()
//{
//    for(AbstractTimingManager* timingManager : model_.getAllTimingManagersContainer())
//    {
//        timingManager->startMovement();
//    }
//}
//
//void Model::stopAllCharacters()
//{
//    for(AbstractTimingManager* timingManager : model_.getAllTimingManagersContainer())
//    {
//        timingManager->stopMovement();
//    }
//}

void Model::startAllCharacters()
{
    for(AbstractTimingManager* timingManager : getAllTimingManagersContainer())
    {
        timingManager->startMovement();
    }
}

void Model::stopAllCharacters()
{
    for(AbstractTimingManager* timingManager : getAllTimingManagersContainer())
    {
        timingManager->stopMovement();
    }
}
//
//void Controller::togglePause()
//{
//    if(model_.getGameStateManager().isRunning())
//    {
//        stopAllCharacters();
//        model_.getGameStateManager().togglePause();
//    }
//    else if(model_.getGameStateManager().isPaused())
//    {
//        startAllCharacters();
//        model_.getGameStateManager().togglePause();
//    }
//}

void Model::togglePause()
{
    if(getGameStateManager().isRunning())
    {
        stopAllCharacters();
        getGameStateManager().togglePause();
    }
    else if(getGameStateManager().isPaused())
    {
        startAllCharacters();
        getGameStateManager().togglePause();
    }
}

void Model::addBallsToScene()
{
    std::set<Foodball>& foodballs = ballItemsManager_->getFoodballs();
    std::set<Powerball>& powerballs = ballItemsManager_->getPowerballs();

    for(const Foodball& foodball : foodballs)
    {
        scene_->addItem(&const_cast<Foodball&>(foodball));
    }

    for(const Powerball& powerball : powerballs)
    {
        scene_->addItem(&const_cast<Powerball&>(powerball));
    }
}
