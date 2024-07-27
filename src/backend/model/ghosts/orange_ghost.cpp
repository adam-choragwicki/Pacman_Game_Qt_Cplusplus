#include "model/ghosts/orange_ghost.h"

OrangeGhost::OrangeGhost() : AbstractGhost(Config::StartingCoordinates::ORANGE_GHOST, INITIAL_DIRECTION, MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT, IMAGES_URLS)
{}
