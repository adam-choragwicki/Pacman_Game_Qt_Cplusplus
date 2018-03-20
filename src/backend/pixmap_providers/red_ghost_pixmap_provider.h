#pragma once

#include "abstract_ghost_pixmap_provider.h"
#include <QString>

class RedGhostPixmapProvider : public AbstractGhostPixmapProvider
{
public:
    RedGhostPixmapProvider();

private:
    inline static const std::array<QString, 6> IMAGES_URLS{":/ghosts/red/ghost_red_right_1.png", ":/ghosts/red/ghost_red_right_2.png", ":/ghosts/red/ghost_red_up_1.png", ":/ghosts/red/ghost_red_up_2.png", ":/ghosts/red/ghost_red_down_1.png",
                                                           ":/ghosts/red/ghost_red_down_2.png"};
};
