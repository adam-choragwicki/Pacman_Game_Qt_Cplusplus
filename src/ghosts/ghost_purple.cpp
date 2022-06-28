#include "ghosts/ghost_purple.h"

GhostPurple::GhostPurple(const GameMap& gameMap) : GhostBase(startingCoordinates_, startTimeout_, gameMap)
{
    loadImages(getImagesUrls());
}

GhostPurple::~GhostPurple()
{

}

void GhostPurple::reset()
{
    GhostBase::reset();
    setCoordinates(startingCoordinates_);
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
