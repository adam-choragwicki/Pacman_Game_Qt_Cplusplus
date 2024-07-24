#include "model/ghosts/red_ghost.h"

RedGhost::RedGhost() : AbstractGhost(Config::StartingCoordinates::RED_GHOST, Config::InitialDirection::RED_GHOST, Config::MoveOutOfTheStartingBoxTimeout::RED_GHOST)
{
    loadImages(IMAGES_URLS);
}
