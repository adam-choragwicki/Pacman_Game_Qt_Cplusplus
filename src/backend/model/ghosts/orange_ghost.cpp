#include "model/ghosts/orange_ghost.h"
#include "pixmap_providers/orange_ghost_pixmap_provider.h"

OrangeGhost::OrangeGhost(OrangeGhostPixmapProvider* pixmapProvider) : AbstractGhost(STARTING_COORDINATES, INITIAL_DIRECTION, MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT, pixmapProvider)
{}
