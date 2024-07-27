#include "model/ghosts/red_ghost.h"

RedGhost::RedGhost() : AbstractGhost(Config::StartingCoordinates::RED_GHOST, INITIAL_DIRECTION, MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT, IMAGES_URLS)
{}
