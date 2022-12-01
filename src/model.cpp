#include "model.h"

Model::Model()
{
    gameMap_ = std::make_unique<GameMap>();
    ballItemsManager_ = std::make_unique<BallItemsManager>(*gameMap_);

    pacman_ = std::make_unique<Pacman>(*gameMap_);
    blueGhost_ = std::make_unique<BlueGhost>(*gameMap_);
    orangeGhost_ = std::make_unique<OrangeGhost>(*gameMap_);
    purpleGhost_ = std::make_unique<PurpleGhost>(*gameMap_);
    redGhost_ = std::make_unique<RedGhost>(*gameMap_);

    movableCharacters = {pacman_.get(), blueGhost_.get(), orangeGhost_.get(), purpleGhost_.get(), redGhost_.get()};
    ghosts_ = {blueGhost_.get(), orangeGhost_.get(), purpleGhost_.get(), redGhost_.get()};

    gameState_ = GameState::BEFORE_FIRST_RUN;
}

void Model::reset()
{
    for(auto& movableCharacter : movableCharacters)
    {
        movableCharacter->reset();
    }

    ballItemsManager_->resetBalls();
}
