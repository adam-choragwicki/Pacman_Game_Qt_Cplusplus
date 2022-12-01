#include "ghosts/purple_ghost.h"

PurpleGhost::PurpleGhost(const GameMap& gameMap) : AbstractGhost(STARTING_COORDINATES, START_TIMEOUT, gameMap)
{

}

void PurpleGhost::reset()
{
    AbstractGhost::reset();
    setCoordinates(STARTING_COORDINATES);
}
