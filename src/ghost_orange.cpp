#include "ghost_orange.h"

GhostOrange::GhostOrange() : GhostBase(startingX_, startingY_, startTimeout_)
{
    loadImages(getImagesUrls());
}

void GhostOrange::reset()
{
    GhostBase::reset();
    setCoordinates(startingX_, startingY_);
}

QVector<std::string> GhostOrange::getImagesUrls()
{
    QVector<std::string> imagesUrl{
            ":/ghost/images/ghost/ghost_orange_left_1.png",
            ":/ghost/images/ghost/ghost_orange_left_2.png",
            ":/ghost/images/ghost/ghost_orange_right_1.png",
            ":/ghost/images/ghost/ghost_orange_right_2.png",
            ":/ghost/images/ghost/ghost_orange_up_1.png",
            ":/ghost/images/ghost/ghost_orange_up_2.png",
            ":/ghost/images/ghost/ghost_orange_down_1.png",
            ":/ghost/images/ghost/ghost_orange_down_2.png",

            ":/ghost/images/ghost/ghost_scared_blue_1.png",
            ":/ghost/images/ghost/ghost_scared_blue_2.png",
            ":/ghost/images/ghost/ghost_scared_white_1.png",
            ":/ghost/images/ghost/ghost_scared_white_2.png",
    };

    return imagesUrl;
}
