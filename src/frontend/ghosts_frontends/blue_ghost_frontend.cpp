#include "blue_ghost_frontend.h"

BlueGhostFrontend::BlueGhostFrontend(const BlueGhost& blueGhost) : AbstractGhostFrontend(blueGhost)
{
    loadImages(BlueGhostImages::IMAGES_URLS);
}
