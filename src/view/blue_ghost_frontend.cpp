#include "view/blue_ghost_frontend.h"

BlueGhostFrontend::BlueGhostFrontend(BlueGhost* blueGhost) : AbstractGhostFrontend(blueGhost)
{
    loadImages(IMAGES_URLS);
}
