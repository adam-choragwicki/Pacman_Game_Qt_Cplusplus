#include "view/orange_ghost_frontend.h"

OrangeGhostFrontend::OrangeGhostFrontend(OrangeGhost* orangeGhost) : AbstractGhostFrontend(orangeGhost)
{
    loadImages(IMAGES_URLS);
}
