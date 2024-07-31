#include "scared_ghost_pixmap_provider.h"
#include "pixmap_loader.h"

void ScaredGhostPixmapProvider::initializePixmaps()
{
    scaredBluePixmaps_[0] = std::make_unique<QPixmap>();
    scaredBluePixmaps_[1] = std::make_unique<QPixmap>();
    scaredWhitePixmaps_[0] = std::make_unique<QPixmap>();
    scaredWhitePixmaps_[1] = std::make_unique<QPixmap>();

    const std::vector<PixmapLoader::PixmapEntry> pixmapEntries = {{scaredBluePixmaps_[0].get(),  ":/ghosts/scared_blue/ghost_scared_blue_1.png"},
                                                                  {scaredBluePixmaps_[1].get(),  ":/ghosts/scared_blue/ghost_scared_blue_2.png"},
                                                                  {scaredWhitePixmaps_[0].get(), ":/ghosts/scared_white/ghost_scared_white_1.png"},
                                                                  {scaredWhitePixmaps_[1].get(), ":/ghosts/scared_white/ghost_scared_white_2.png"}};

    PixmapLoader::loadPixmaps(pixmapEntries);
}

const QPixmap& ScaredGhostPixmapProvider::getScaredBluePixmap(int animationPhase) const
{
    if(animationPhase >= ANIMATION_PHASES_COUNT)
    {
        throw std::out_of_range("Invalid animation phase");
    }

    return *scaredBluePixmaps_[animationPhase];
}

const QPixmap& ScaredGhostPixmapProvider::getScaredWhitePixmap(int animationPhase) const
{
    if(animationPhase >= ANIMATION_PHASES_COUNT)
    {
        throw std::out_of_range("Invalid animation phase");
    }

    return *scaredWhitePixmaps_[animationPhase];
}
