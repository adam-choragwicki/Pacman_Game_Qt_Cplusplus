#include "model/ghosts/orange_ghost.h"

OrangeGhost::OrangeGhost(std::shared_ptr<GhostPixmapProvider> pixmapProvider) : AbstractGhost(STARTING_COORDINATES, INITIAL_DIRECTION, MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT, pixmapProvider)
{}
