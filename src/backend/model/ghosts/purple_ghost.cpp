#include "model/ghosts/purple_ghost.h"

PurpleGhost::PurpleGhost() : AbstractGhost(Config::StartingCoordinates::PURPLE_GHOST, INITIAL_DIRECTION, MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT, IMAGES_URLS)
{}
