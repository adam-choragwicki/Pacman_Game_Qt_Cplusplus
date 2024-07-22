#include "model/ghosts/blue_ghost.h"
#include "images_urls.h"

BlueGhost::BlueGhost() : AbstractGhost(Config::StartingCoordinates::BLUE_GHOST, Config::InitialDirection::BLUE_GHOST, Config::MoveOutOfTheStartingBoxTimeout::BLUE_GHOST)
{
    loadImages(BlueGhostImages::IMAGES_URLS);
}
