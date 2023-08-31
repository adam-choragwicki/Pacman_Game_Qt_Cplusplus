#include "purple_ghost_frontend.h"

PurpleGhostFrontend::PurpleGhostFrontend(const PurpleGhost& purpleGhost) : AbstractGhostFrontend(purpleGhost)
{
    loadImages(PurpleGhostImages::IMAGES_URLS);
}
