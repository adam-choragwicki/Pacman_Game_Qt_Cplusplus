#include "ghosts/orange_ghost.h"

OrangeGhost::OrangeGhost(const GameMap& gameMap) : AbstractGhost(STARTING_COORDINATES, START_TIMEOUT, gameMap)
{

}

void OrangeGhost::reset()
{
    AbstractGhost::reset();
    setCoordinates(STARTING_COORDINATES);
}
