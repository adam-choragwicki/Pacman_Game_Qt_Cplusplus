#include "model/ghosts/blue_ghost.h"

BlueGhost::BlueGhost() : AbstractGhost(Config::StartingCoordinates::BLUE_GHOST, INITIAL_DIRECTION, MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT, IMAGES_URLS)
{}
