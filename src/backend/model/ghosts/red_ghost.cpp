#include "model/ghosts/red_ghost.h"
#include "images_urls.h"

RedGhost::RedGhost() : AbstractGhost(Config::StartingCoordinates::RED_GHOST, Config::InitialDirection::RED_GHOST)
{
    loadImages(RedGhostImages::IMAGES_URLS);
}
