#include "model/ghosts/purple_ghost.h"

PurpleGhost::PurpleGhost() : AbstractGhost(Config::StartingCoordinates::PURPLE_GHOST, Config::InitialDirection::PURPLE_GHOST, Config::MoveOutOfTheStartingBoxTimeout::PURPLE_GHOST, IMAGES_URLS)
{}
