#include "ghosts/blue_ghost.h"

BlueGhost::BlueGhost(const GameMap& gameMap) : AbstractGhost(STARTING_COORDINATES, START_TIMEOUT, gameMap)
{

}

void BlueGhost::reset()
{
    AbstractGhost::reset();
    setCoordinates(STARTING_COORDINATES);
}
