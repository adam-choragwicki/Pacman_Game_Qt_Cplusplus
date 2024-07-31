#include "model/ghosts/red_ghost.h"

RedGhost::RedGhost(std::shared_ptr<GhostPixmapProvider> pixmapProvider) : AbstractGhost(STARTING_COORDINATES, INITIAL_DIRECTION, MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT, pixmapProvider)
{}
