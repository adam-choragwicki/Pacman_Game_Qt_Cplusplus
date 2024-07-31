#pragma once

#include "abstract_ghost_pixmap_provider.h"
#include <QString>

class OrangeGhostPixmapProvider : public AbstractGhostPixmapProvider
{
public:
    OrangeGhostPixmapProvider();

private:
    inline static const std::array<QString, 6> IMAGES_URLS{":/ghosts/orange/ghost_orange_right_1.png", ":/ghosts/orange/ghost_orange_right_2.png", ":/ghosts/orange/ghost_orange_up_1.png", ":/ghosts/orange/ghost_orange_up_2.png",
                                                           ":/ghosts/orange/ghost_orange_down_1.png", ":/ghosts/orange/ghost_orange_down_2.png"};

};
