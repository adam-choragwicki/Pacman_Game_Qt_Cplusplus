#include "red_ghost_frontend.h"

RedGhostFrontend::RedGhostFrontend(const RedGhost& redGhost) : AbstractGhostFrontend(redGhost)
{
    loadImages(RedGhostImages::IMAGES_URLS);
}
