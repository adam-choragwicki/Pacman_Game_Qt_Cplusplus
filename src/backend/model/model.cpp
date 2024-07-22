#include "model.h"

#include "path_points.h"
#include "pacman.h"
#include "ball_items_manager.h"
#include "ghosts/red_ghost.h"
#include "ghosts/purple_ghost.h"
#include "ghosts/blue_ghost.h"
#include "ghosts/orange_ghost.h"

#include "score_manager.h"
#include "game_state_manager.h"

#include "pacman_movement_manager.h"
#include "ghost_movement_manager.h"

#include "balls/foodball.h"
#include "balls/powerball.h"
#include "screen_text_display.h"

#include "score_display.h"

#include "spdlog/spdlog.h"

#include <QtWidgets/QGraphicsScene>

Model::Model()
{
    spdlog::debug("Initializing model");

    initScene();

    pathPoints_ = std::make_unique<PathPoints>();

    pacman_ = std::make_unique<Pacman>();
    blueGhost_ = std::make_unique<BlueGhost>();
    orangeGhost_ = std::make_unique<OrangeGhost>();
    purpleGhost_ = std::make_unique<PurpleGhost>();
    redGhost_ = std::make_unique<RedGhost>();

    scoreManager_ = std::make_unique<ScoreManager>();
    scoreDisplay_ = std::make_unique<ScoreDisplay>(*scoreManager_);

    pacmanMovementManager_ = std::make_unique<PacmanMovementManager>();
    ghostMovementManager_ = std::make_unique<GhostMovementManager>();

    screenTextDisplay_ = std::make_unique<ScreenTextDisplay>(*scoreManager_);

    ballItemsManager_ = std::make_unique<BallItemsManager>(*pathPoints_);

    addItemsToScene();
}

void Model::reset()
{
    spdlog::debug("Model reset");

    ballItemsManager_->reset();

    pacman_->reset();
    blueGhost_->reset();
    orangeGhost_->reset();
    purpleGhost_->reset();
    redGhost_->reset();

    addItemsToScene();
}

void Model::initScene()
{
    const int ARENA_WIDTH_PX = 614;
    const int ARENA_HEIGHT_PX = 730;

    scene_ = std::make_unique<QGraphicsScene>(0, 0, ARENA_WIDTH_PX, ARENA_HEIGHT_PX);
}

void Model::addItemsToScene()
{
    addBallsToScene();

    scene_->addItem(pacman_.get());
    scene_->addItem(blueGhost_.get());
    scene_->addItem(orangeGhost_.get());
    scene_->addItem(purpleGhost_.get());
    scene_->addItem(redGhost_.get());

    scene_->addItem(screenTextDisplay_.get());

    scene_->addItem(scoreDisplay_.get());
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
