#include "model/ghosts/blue_ghost.h"
#include "images_urls.h"

BlueGhost::BlueGhost() : AbstractGhost(Config::StartingCoordinates::BLUE_GHOST, Config::InitialDirection::BLUE_GHOST, Config::MoveOutOfTheStartingBoxTimeout::BLUE_GHOST)
{
    loadImages(BlueGhostImages::IMAGES_URLS);
}


//blueGhostTimingManager_ = std::make_unique<GhostTimingManager>(*blueGhost_, Config::StartTimeout::BLUE_GHOST);
//orangeGhostTimingManager_ = std::make_unique<GhostTimingManager>(*orangeGhost_, Config::StartTimeout::ORANGE_GHOST);
//purpleGhostTimingManager_ = std::make_unique<GhostTimingManager>(*purpleGhost_, Config::StartTimeout::PURPLE_GHOST);
//redGhostTimingManager_ = std::make_unique<GhostTimingManager>(*redGhost_, Config::StartTimeout::RED_GHOST);
