#include "ghost_purple.h"

GhostPurple::GhostPurple() : GhostBase(startingX_, startingY_, startTimeout_)
{
    loadImages(getImagesUrls());
}

void GhostPurple::reset()
{
    GhostBase::reset();
    setCoordinates(startingX_, startingY_);
}

QVector<std::string> GhostPurple::getImagesUrls()
{
    QVector<std::string> imagesUrl{
            ":/ghost/images/ghost/ghost_purple_left_1.png",
            ":/ghost/images/ghost/ghost_purple_left_2.png",
            ":/ghost/images/ghost/ghost_purple_right_1.png",
            ":/ghost/images/ghost/ghost_purple_right_2.png",
            ":/ghost/images/ghost/ghost_purple_up_1.png",
            ":/ghost/images/ghost/ghost_purple_up_2.png",
            ":/ghost/images/ghost/ghost_purple_down_1.png",
            ":/ghost/images/ghost/ghost_purple_down_2.png",

            ":/ghost/images/ghost/ghost_scared_blue_1.png",
            ":/ghost/images/ghost/ghost_scared_blue_2.png",
            ":/ghost/images/ghost/ghost_scared_white_1.png",
            ":/ghost/images/ghost/ghost_scared_white_2.png",
    };

    return imagesUrl;
}
