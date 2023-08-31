#include "model/model.h"

Model::Model()
{
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

    groupObjectsIntoContainers();
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
}
