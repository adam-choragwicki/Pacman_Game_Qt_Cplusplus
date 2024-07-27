#include "model/ghosts/red_ghost.h"

RedGhost::RedGhost() : AbstractGhost(Config::StartingCoordinates::RED_GHOST, Config::InitialDirection::RED_GHOST, MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT, IMAGES_URLS)
{}
