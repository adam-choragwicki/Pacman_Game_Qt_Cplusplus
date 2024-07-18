#include "model/ghosts/purple_ghost.h"
#include "images_urls.h"

PurpleGhost::PurpleGhost() : AbstractGhost(Config::StartingCoordinates::PURPLE_GHOST, Config::InitialDirection::PURPLE_GHOST)
{
    loadImages(PurpleGhostImages::IMAGES_URLS);
}
