#include "view/abstract_ghost_frontend.h"

AbstractGhostFrontend::AbstractGhostFrontend(AbstractGhost* abstractGhost)
{
    abstractGhost_ = abstractGhost;
}

void AbstractGhostFrontend::loadImages(const std::array<std::string, 12>& imagesUrls)
{
    const std::map<QPixmap*, std::string> pixmapToPathMapping{{&left1Pixmap_,        imagesUrls.at(0)},
                                                              {&left2Pixmap_,        imagesUrls.at(1)},

                                                              {&right1Pixmap_,       imagesUrls.at(2)},
                                                              {&right2Pixmap_,       imagesUrls.at(3)},

                                                              {&up1Pixmap_,          imagesUrls.at(4)},
                                                              {&up2Pixmap_,          imagesUrls.at(5)},

                                                              {&down1Pixmap_,        imagesUrls.at(6)},
                                                              {&down2Pixmap_,        imagesUrls.at(7)},

                                                              {&scaredBlue1Pixmap_,  imagesUrls.at(8)},
                                                              {&scaredBlue2Pixmap_,  imagesUrls.at(9)},

                                                              {&scaredWhite1Pixmap_, imagesUrls.at(10)},
                                                              {&scaredWhite2Pixmap_, imagesUrls.at(11)}};

    auto loadImage = [](const std::pair<QPixmap*, std::string>& pixmapToPathPair)
    {
        auto& [pixmap, path] = pixmapToPathPair;
        return pixmap->load(QString::fromStdString(path));
    };

    if(!std::all_of(pixmapToPathMapping.cbegin(), pixmapToPathMapping.cend(), loadImage))
    {
        throw std::runtime_error("Cannot load Ghost images");
    }
}
