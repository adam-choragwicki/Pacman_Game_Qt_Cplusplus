#include "model/ghosts/blue_ghost.h"

BlueGhost::BlueGhost(std::shared_ptr<GhostPixmapProvider> pixmapProvider) : AbstractGhost(STARTING_COORDINATES, INITIAL_DIRECTION, MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT, pixmapProvider)
{}
