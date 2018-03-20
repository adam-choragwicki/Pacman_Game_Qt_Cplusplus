#pragma once

#include "abstract_ghost_pixmap_provider.h"
#include <QString>

class PurpleGhostPixmapProvider : public AbstractGhostPixmapProvider
{
public:
    PurpleGhostPixmapProvider();

private:
    inline static const std::array<QString, 6> IMAGES_URLS{":/ghosts/purple/ghost_purple_right_1.png", ":/ghosts/purple/ghost_purple_right_2.png", ":/ghosts/purple/ghost_purple_up_1.png", ":/ghosts/purple/ghost_purple_up_2.png",
                                                           ":/ghosts/purple/ghost_purple_down_1.png", ":/ghosts/purple/ghost_purple_down_2.png"};
};
