#include "orange_ghost_frontend.h"

OrangeGhostFrontend::OrangeGhostFrontend(const OrangeGhost& orangeGhost) : AbstractGhostFrontend(orangeGhost)
{
    loadImages(OrangeGhostImages::IMAGES_URLS);
}
