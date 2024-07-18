#include "model/ghosts/orange_ghost.h"
#include "images_urls.h"

OrangeGhost::OrangeGhost() : AbstractGhost(Config::StartingCoordinates::ORANGE_GHOST, Config::InitialDirection::ORANGE_GHOST)
{
    loadImages(OrangeGhostImages::IMAGES_URLS);
}
