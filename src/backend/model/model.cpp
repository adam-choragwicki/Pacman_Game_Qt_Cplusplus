#include "model.h"
#include "spdlog/spdlog.h"

Model::Model()
{
    spdlog::debug("Initializing model");

    scene_ = std::make_unique<GraphicsScene>();

    pathPoints_ = std::make_unique<PathPoints>();

    pacmanPixmapProvider_ = std::make_unique<PacmanPixmapProvider>();

    blueGhostPixmapProvider_ = std::make_unique<BlueGhostPixmapProvider>();
    orangeGhostPixmapProvider_ = std::make_unique<OrangeGhostPixmapProvider>();
    purpleGhostPixmapProvider_ = std::make_unique<PurpleGhostPixmapProvider>();
    redGhostPixmapProvider_ = std::make_unique<RedGhostPixmapProvider>();

    pacman_ = std::make_unique<Pacman>(pacmanPixmapProvider_.get());
    blueGhost_ = std::make_unique<BlueGhost>(blueGhostPixmapProvider_.get());
    orangeGhost_ = std::make_unique<OrangeGhost>(orangeGhostPixmapProvider_.get());
    purpleGhost_ = std::make_unique<PurpleGhost>(purpleGhostPixmapProvider_.get());
    redGhost_ = std::make_unique<RedGhost>(redGhostPixmapProvider_.get());

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

    scoreManager_->reset();

    spdlog::debug("Items on scene after reset: {}", scene_->items().size());
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
