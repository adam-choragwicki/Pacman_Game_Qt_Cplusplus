#include "model/ghosts/purple_ghost.h"
#include "pixmap_providers/purple_ghost_pixmap_provider.h"

PurpleGhost::PurpleGhost(PurpleGhostPixmapProvider* pixmapProvider) :
        AbstractGhost(STARTING_COORDINATES, INITIAL_DIRECTION, MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT, pixmapProvider)
{}
