#pragma once

#include "abstract_ghost_pixmap_provider.h"
#include <QString>

class BlueGhostPixmapProvider : public AbstractGhostPixmapProvider
{
public:
    BlueGhostPixmapProvider();

private:
    inline static const std::array<QString, 6> IMAGES_URLS{":/ghosts/blue/ghost_blue_right_1.png", ":/ghosts/blue/ghost_blue_right_2.png", ":/ghosts/blue/ghost_blue_up_1.png", ":/ghosts/blue/ghost_blue_up_2.png",
                                                           ":/ghosts/blue/ghost_blue_down_1.png", ":/ghosts/blue/ghost_blue_down_2.png"};

};
