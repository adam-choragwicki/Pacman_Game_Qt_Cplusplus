#include "model/ghosts/purple_ghost.h"

PurpleGhost::PurpleGhost(PurpleGhostPixmapProvider* pixmapProvider, ScaredGhostPixmapProvider* scaredGhostPixmapProvider) :
        AbstractGhost(STARTING_COORDINATES, INITIAL_DIRECTION, MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT, pixmapProvider, scaredGhostPixmapProvider)
{}
