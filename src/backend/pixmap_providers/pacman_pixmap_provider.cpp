#include "pacman_pixmap_provider.h"
#include "pixmap_loader.h"
#include "pixmap_manager.h"
#include "common.h"

PacmanPixmapProvider::PacmanPixmapProvider()
{
    initializePixmaps();
}

void PacmanPixmapProvider::initializePixmaps()
{
    const std::vector<PixmapLoader::PixmapEntry> pixmapEntries = {{&rightPixmaps_[0], ":/pacman/pacman_right_close.png"},
                                                                  {&rightPixmaps_[1], ":/pacman/pacman_right_open_1.png"},
                                                                  {&rightPixmaps_[2], ":/pacman/pacman_right_open_2.png"},
                                                                  {&rightPixmaps_[3], ":/pacman/pacman_right_open_3.png"}};

    PixmapLoader::loadPixmaps(pixmapEntries);

    for(int i = 0; i < ANIMATION_PHASES_COUNT; ++i)
    {
        rightPixmaps_[i] = PixmapManager::scalePixmap(&rightPixmaps_[i], QRect(0, 0, 30, 30));
        leftPixmaps_[i] = PixmapManager::mirrorPixmapHorizontally(&rightPixmaps_[i]);
        upPixmaps_[i] = PixmapManager::rotatePixmap90DegreesCounterclockwise(&rightPixmaps_[i]);
        downPixmaps_[i] = PixmapManager::rotatePixmap90DegreesClockwise(&rightPixmaps_[i]);
    }
}

const QPixmap& PacmanPixmapProvider::getPixmap(Direction direction, int animationPhase) const
{
    switch(direction)
    {
        case Direction::LEFT:
            return leftPixmaps_[animationPhase];
        case Direction::RIGHT:
            return rightPixmaps_[animationPhase];
        case Direction::UP:
            return upPixmaps_[animationPhase];
        case Direction::DOWN:
            return downPixmaps_[animationPhase];
        default:
            throw std::runtime_error("Cannot get pixmap, wrong direction");
    }
}
