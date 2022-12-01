#include "view/red_ghost_frontend.h"

RedGhostFrontend::RedGhostFrontend(RedGhost* redGhost) : AbstractGhostFrontend(redGhost)
{
    loadImages(IMAGES_URLS);
}
