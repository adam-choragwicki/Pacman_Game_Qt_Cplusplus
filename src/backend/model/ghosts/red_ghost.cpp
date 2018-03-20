#include "model/ghosts/red_ghost.h"
#include "pixmap_providers/red_ghost_pixmap_provider.h"

RedGhost::RedGhost(RedGhostPixmapProvider* pixmapProvider) : AbstractGhost(STARTING_COORDINATES, INITIAL_DIRECTION, MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT, pixmapProvider)
{}
