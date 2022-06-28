#include "ghosts/ghost_blue.h"

GhostBlue::GhostBlue(const GameMap& gameMap) : GhostBase(startingCoordinates_, startTimeout_, gameMap)
{
    loadImages(getImagesUrls());
}

GhostBlue::~GhostBlue()
{

}

void GhostBlue::reset()
{
    GhostBase::reset();
    setCoordinates(startingCoordinates_);
}

QVector<std::string> GhostBlue::getImagesUrls()
{
    QVector<std::string> imagesUrl{
            ":/ghost/images/ghost/ghost_blue_left_1.png",
            ":/ghost/images/ghost/ghost_blue_left_2.png",
            ":/ghost/images/ghost/ghost_blue_right_1.png",
            ":/ghost/images/ghost/ghost_blue_right_2.png",
            ":/ghost/images/ghost/ghost_blue_up_1.png",
            ":/ghost/images/ghost/ghost_blue_up_2.png",
            ":/ghost/images/ghost/ghost_blue_down_1.png",
            ":/ghost/images/ghost/ghost_blue_down_2.png",

            ":/ghost/images/ghost/ghost_scared_blue_1.png",
            ":/ghost/images/ghost/ghost_scared_blue_2.png",
            ":/ghost/images/ghost/ghost_scared_white_1.png",
            ":/ghost/images/ghost/ghost_scared_white_2.png",
    };

    return imagesUrl;
}
