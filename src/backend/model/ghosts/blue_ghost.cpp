#include "model/ghosts/blue_ghost.h"
#include "pixmap_providers/blue_ghost_pixmap_provider.h"

BlueGhost::BlueGhost(BlueGhostPixmapProvider* pixmapProvider) :
        AbstractGhost(STARTING_COORDINATES, INITIAL_DIRECTION, MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT, pixmapProvider)
{}
