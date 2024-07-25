#include "model.h"
#include "spdlog/spdlog.h"

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

    pelletsManager_ = std::make_unique<PelletsManager>(*pathPoints_);

    whatToDrawManager_ = std::make_unique<WhatToDrawManager>();

    addItemsToScene();

    spdlog::debug("Items on scene: {}", scene_->items().size());
}

void Model::reset()
{
    spdlog::debug("Model reset");

    pelletsManager_->reset();

    addPelletsToScene();

    pacman_->reset();
    blueGhost_->reset();
    orangeGhost_->reset();
    purpleGhost_->reset();
    redGhost_->reset();

    scoreManager_->resetScore();

    spdlog::debug("Items on scene after reset: {}", scene_->items().size());
}

void Model::initScene()
{
    const int ARENA_WIDTH_PX = 614;
    const int ARENA_HEIGHT_PX = 730;

    scene_ = std::make_unique<QGraphicsScene>(0, 0, ARENA_WIDTH_PX, ARENA_HEIGHT_PX);
}

void Model::addItemsToScene()
{
    addPelletsToScene();

    scene_->addItem(pacman_.get());
    scene_->addItem(blueGhost_.get());
    scene_->addItem(orangeGhost_.get());
    scene_->addItem(purpleGhost_.get());
    scene_->addItem(redGhost_.get());

    scene_->addItem(screenTextDisplay_.get());

    scene_->addItem(scoreDisplay_.get());
}

void Model::addPelletsToScene()
{
    std::set<StandardPellet>& standardPellets = pelletsManager_->getStandardPellets();
    std::set<PowerPellet>& powerPellets = pelletsManager_->getPowerPellets();

    for(const StandardPellet& standardPellet : standardPellets)
    {
        scene_->addItem(&const_cast<StandardPellet&>(standardPellet));
    }

    for(const PowerPellet& powerPellet : powerPellets)
    {
        scene_->addItem(&const_cast<PowerPellet&>(powerPellet));
    }
}
