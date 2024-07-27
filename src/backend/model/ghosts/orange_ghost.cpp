#include "model/ghosts/orange_ghost.h"

OrangeGhost::OrangeGhost() : AbstractGhost(Config::StartingCoordinates::ORANGE_GHOST, Config::InitialDirection::ORANGE_GHOST, Config::MoveOutOfTheStartingBoxTimeout::ORANGE_GHOST)
{
    loadPixmaps(IMAGES_URLS);
}
