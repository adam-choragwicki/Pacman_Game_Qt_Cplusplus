#include "abstract_ghost_pixmap_provider.h"
#include "pixmap_loader.h"
#include "pixmap_manager.h"
#include <QDebug>
#include "common.h"

AbstractGhostPixmapProvider::AbstractGhostPixmapProvider(const std::array<QString, 6>& imageUrls)
{
    initializePixmaps(imageUrls);
}

void AbstractGhostPixmapProvider::initializePixmaps(const std::array<QString, 6>& imageUrls)
{
    const std::vector<PixmapLoader::PixmapEntry> pixmapEntries{{&rightPixmaps_[0], imageUrls.at(0)},
                                                               {&rightPixmaps_[1], imageUrls.at(1)},

                                                               {&upPixmaps_[0],    imageUrls.at(2)},
                                                               {&upPixmaps_[1],    imageUrls.at(3)},

                                                               {&downPixmaps_[0],  imageUrls.at(4)},
                                                               {&downPixmaps_[1],  imageUrls.at(5)}};

    PixmapLoader::loadPixmaps(pixmapEntries);

    for(int i = 0; i < ANIMATION_PHASES_COUNT; ++i)
    {
        rightPixmaps_[i] = PixmapManager::scalePixmap(&rightPixmaps_[i], QRect(0, 0, 30, 30));
        upPixmaps_[i] = PixmapManager::scalePixmap(&upPixmaps_[i], QRect(0, 0, 30, 30));
        downPixmaps_[i] = PixmapManager::scalePixmap(&downPixmaps_[i], QRect(0, 0, 30, 30));

        /* Mirror right pixmap horizontally to obtain left pixmap */
        leftPixmaps_[i] = PixmapManager::mirrorPixmapHorizontally(&rightPixmaps_[i]);
    }
}

const QPixmap& AbstractGhostPixmapProvider::getPixmap(Direction direction, int animationPhase) const
{
    if(animationPhase >= ANIMATION_PHASES_COUNT)
    {
        throw std::out_of_range("Invalid animation phase");
    }

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
            throw std::invalid_argument("Invalid direction");
    }
}
