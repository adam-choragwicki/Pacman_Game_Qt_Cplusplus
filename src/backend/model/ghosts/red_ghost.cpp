#include "model/ghosts/red_ghost.h"

RedGhost::RedGhost(RedGhostPixmapProvider* pixmapProvider, ScaredGhostPixmapProvider* scaredGhostPixmapProvider) : AbstractGhost(STARTING_COORDINATES, INITIAL_DIRECTION, MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT, pixmapProvider, scaredGhostPixmapProvider)
{}
