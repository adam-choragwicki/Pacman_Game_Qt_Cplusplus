#include "ghost_pixmap_provider.h"
#include "pixmap_loader.h"
#include "pixmap_manager.h"
#include <QDebug>

GhostPixmapProvider::GhostPixmapProvider()
{
    initializePixmaps();
}

void GhostPixmapProvider::initializePixmaps()
{
    const std::vector<PixmapLoader::PixmapEntry> pixmapEntries = {{&rightPixmaps_[0],       ":/ghosts/right_1.png"},
                                                                  {&rightPixmaps_[1],       ":/ghosts/right_2.png"},
                                                                  {&upPixmaps_[0],          ":/ghosts/up_1.png"},
                                                                  {&upPixmaps_[1],          ":/ghosts/up_2.png"},
                                                                  {&downPixmaps_[0],        ":/ghosts/down_1.png"},
                                                                  {&downPixmaps_[1],        ":/ghosts/down_2.png"},
                                                                  {&scaredBluePixmaps_[0],  ":/ghosts/scared_blue_1.png"},
                                                                  {&scaredBluePixmaps_[1],  ":/ghosts/scared_blue_2.png"},
                                                                  {&scaredWhitePixmaps_[0], ":/ghosts/scared_white_1.png"},
                                                                  {&scaredWhitePixmaps_[1], ":/ghosts/scared_white_2.png"}};

    PixmapLoader::loadPixmaps(pixmapEntries);

    for(int i = 0; i < ANIMATION_PHASES_COUNT; ++i)
    {
        rightPixmaps_[i] = PixmapManager::scalePixmap(&rightPixmaps_[i], QRect());
        upPixmaps_[i] = PixmapManager::scalePixmap(&upPixmaps_[i], QRect());
        downPixmaps_[i] = PixmapManager::scalePixmap(&downPixmaps_[i], QRect());
        scaredBluePixmaps_[i] = PixmapManager::scalePixmap(&scaredBluePixmaps_[i], QRect());
        scaredWhitePixmaps_[i] = PixmapManager::scalePixmap(&scaredWhitePixmaps_[i], QRect());

        /* Mirror right pixmap horizontally to obtain left pixmap */
        leftPixmaps_[i] = PixmapManager::mirrorPixmapHorizontally(&rightPixmaps_[i]);
    }

    // Debugging: Check if pixmaps are initialized correctly
    for(int i = 0; i < ANIMATION_PHASES_COUNT; ++i)
    {
        qDebug() << "Right pixmap" << i << ": " << !rightPixmaps_[i].isNull();
        qDebug() << "Left pixmap" << i << ": " << !leftPixmaps_[i].isNull();
        qDebug() << "Up pixmap" << i << ": " << !upPixmaps_[i].isNull();
        qDebug() << "Down pixmap" << i << ": " << !downPixmaps_[i].isNull();
        qDebug() << "Scared Blue pixmap" << i << ": " << !scaredBluePixmaps_[i].isNull();
        qDebug() << "Scared White pixmap" << i << ": " << !scaredWhitePixmaps_[i].isNull();
    }
}

const QPixmap& GhostPixmapProvider::getPixmap(Direction direction, int animationPhase) const
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

const QPixmap& GhostPixmapProvider::getScaredBluePixmap(int animationPhase) const
{
    if(animationPhase >= ANIMATION_PHASES_COUNT)
    {
        throw std::out_of_range("Invalid animation phase");
    }

    return scaredBluePixmaps_[animationPhase];
}

const QPixmap& GhostPixmapProvider::getScaredWhitePixmap(int animationPhase) const
{
    if(animationPhase >= ANIMATION_PHASES_COUNT)
    {
        throw std::out_of_range("Invalid animation phase");
    }

    return scaredWhitePixmaps_[animationPhase];
}
