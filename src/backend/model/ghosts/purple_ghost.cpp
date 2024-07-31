#include "model/ghosts/purple_ghost.h"

PurpleGhost::PurpleGhost(std::shared_ptr<GhostPixmapProvider> pixmapProvider) : AbstractGhost(STARTING_COORDINATES, INITIAL_DIRECTION, MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT, pixmapProvider)
{}
