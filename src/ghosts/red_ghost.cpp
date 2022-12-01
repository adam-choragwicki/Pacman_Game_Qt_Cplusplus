#include "ghosts/red_ghost.h"

RedGhost::RedGhost(const GameMap& gameMap) : AbstractGhost(STARTING_COORDINATES, START_TIMEOUT, gameMap)
{

}

void RedGhost::reset()
{
    AbstractGhost::reset();
    setCoordinates(COORDINATES_AFTER_RESPAWN);
}
