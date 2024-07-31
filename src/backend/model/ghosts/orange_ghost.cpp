#include "model/ghosts/orange_ghost.h"

OrangeGhost::OrangeGhost(OrangeGhostPixmapProvider* pixmapProvider, ScaredGhostPixmapProvider* scaredGhostPixmapProvider) : AbstractGhost(STARTING_COORDINATES, INITIAL_DIRECTION, MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT, pixmapProvider,
                                                                                                                                                          scaredGhostPixmapProvider)
{}
