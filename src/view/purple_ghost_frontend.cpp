#include "view/purple_ghost_frontend.h"

PurpleGhostFrontend::PurpleGhostFrontend(PurpleGhost* purpleGhost) : AbstractGhostFrontend(purpleGhost)
{
    loadImages(IMAGES_URLS);
}
