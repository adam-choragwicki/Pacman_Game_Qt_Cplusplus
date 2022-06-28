#include "ghosts/ghost_red.h"

GhostRed::GhostRed(const GameMap& gameMap) : GhostBase(startingCoordinates_, startTimeout_, gameMap)
{
    loadImages(getImagesUrls());
}

GhostRed::~GhostRed()
{

}

void GhostRed::reset()
{
    GhostBase::reset();
    setCoordinates(coordinatesAfterRespawn_);
}

QVector<std::string> GhostRed::getImagesUrls()
{
    QVector<std::string> imagesUrl{
            ":/ghost/images/ghost/ghost_red_right_1.png",
            ":/ghost/images/ghost/ghost_red_right_2.png",
            ":/ghost/images/ghost/ghost_red_up_1.png",
            ":/ghost/images/ghost/ghost_red_up_2.png",
            ":/ghost/images/ghost/ghost_red_down_1.png",
            ":/ghost/images/ghost/ghost_red_down_2.png",
            ":/ghost/images/ghost/ghost_red_left_1.png",
            ":/ghost/images/ghost/ghost_red_left_2.png",

            ":/ghost/images/ghost/ghost_scared_blue_1.png",
            ":/ghost/images/ghost/ghost_scared_blue_2.png",
            ":/ghost/images/ghost/ghost_scared_white_1.png",
            ":/ghost/images/ghost/ghost_scared_white_2.png"
    };

    return imagesUrl;
}
