#include "view/pacman_frontend.h"
#include "log_manager.h"

PacmanFrontend::PacmanFrontend()
{
    loadImages();
}

void PacmanFrontend::loadImages()
{
    const std::map<QPixmap*, std::string> pixmapToPathMapping{{&left1Pixmap_,  ":/pacman/images/pacman/pacman_left_close.png"},
                                                              {&left2Pixmap_,  ":/pacman/images/pacman/pacman_left_open_1.png"},
                                                              {&left3Pixmap_,  ":/pacman/images/pacman/pacman_left_open_2.png"},
                                                              {&left4Pixmap_,  ":/pacman/images/pacman/pacman_left_open_3.png"},

                                                              {&right1Pixmap_, ":/pacman/images/pacman/pacman_right_close.png"},
                                                              {&right2Pixmap_, ":/pacman/images/pacman/pacman_right_open_1.png"},
                                                              {&right3Pixmap_, ":/pacman/images/pacman/pacman_right_open_2.png"},
                                                              {&right4Pixmap_, ":/pacman/images/pacman/pacman_right_open_3.png"},

                                                              {&up1Pixmap_,    ":/pacman/images/pacman/pacman_up_close.png"},
                                                              {&up2Pixmap_,    ":/pacman/images/pacman/pacman_up_open_1.png"},
                                                              {&up3Pixmap_,    ":/pacman/images/pacman/pacman_up_open_2.png"},
                                                              {&up4Pixmap_,    ":/pacman/images/pacman/pacman_up_open_3.png"},

                                                              {&down1Pixmap_,  ":/pacman/images/pacman/pacman_down_close.png"},
                                                              {&down2Pixmap_,  ":/pacman/images/pacman/pacman_down_open_1.png"},
                                                              {&down3Pixmap_,  ":/pacman/images/pacman/pacman_down_open_2.png"},
                                                              {&down4Pixmap_,  ":/pacman/images/pacman/pacman_down_open_3.png"}};

    auto loadImage = [](const std::pair<QPixmap*, std::string>& pixmapToPathPair)
    {
        auto& [pixmap, path] = pixmapToPathPair;
        return pixmap->load(QString::fromStdString(path));
    };

    if(!std::all_of(pixmapToPathMapping.cbegin(), pixmapToPathMapping.cend(), loadImage))
    {
        throw std::runtime_error("Cannot load Pacman images");
    }
}
