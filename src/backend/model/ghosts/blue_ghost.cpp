#include "model/ghosts/blue_ghost.h"

BlueGhost::BlueGhost() : AbstractGhost(Config::StartingCoordinates::BLUE_GHOST, Config::InitialDirection::BLUE_GHOST, Config::MoveOutOfTheStartingBoxTimeout::BLUE_GHOST, IMAGES_URLS)
{}
