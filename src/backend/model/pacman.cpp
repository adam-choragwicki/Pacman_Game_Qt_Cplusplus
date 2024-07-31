#include "model/pacman.h"
#include "pixmap_loader.h"
#include "pixmap_manager.h"
#include <QtGui/QPainter>

Pacman::Pacman() : MovableCharacter(STARTING_COORDINATES, INITIAL_DIRECTION, ANIMATION_SPEED_FACTOR, ANIMATION_PHASES_COUNT)
{
    initializePixmaps();

    direction_ = Direction::LEFT;
}

void Pacman::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    CustomGraphicsItem::paint(painter, option, widget);

    painter->setRenderHint(QPainter::Antialiasing);

    const QPixmap* pixmap;

    switch(direction_)
    {
        case Direction::LEFT:
            pixmap = &leftPixmaps_[animationPhase_];
            break;
        case Direction::RIGHT:
            pixmap = &rightPixmaps_[animationPhase_];
            break;
        case Direction::UP:
            pixmap = &upPixmaps_[animationPhase_];
            break;
        case Direction::DOWN:
            pixmap = &downPixmaps_[animationPhase_];
            break;
        default:
            throw std::runtime_error("Cannot draw Pacman, wrong direction");
    }

    drawPixmapAvoidingArtifacts(painter, pixmap);
}

void Pacman::initializePixmaps()
{
    const std::vector<PixmapLoader::PixmapEntry> pixmapEntries = {{&rightPixmaps_[0], ":/pacman/pacman_right_close.png"},
                                                                  {&rightPixmaps_[1], ":/pacman/pacman_right_open_1.png"},
                                                                  {&rightPixmaps_[2], ":/pacman/pacman_right_open_2.png"},
                                                                  {&rightPixmaps_[3], ":/pacman/pacman_right_open_3.png"}};

    PixmapLoader::loadPixmaps(pixmapEntries);

    for(int i = 0; i < ANIMATION_PHASES_COUNT; ++i)
    {
        rightPixmaps_[i] = PixmapManager::scalePixmap(&rightPixmaps_[i], rect_);
        leftPixmaps_[i] = PixmapManager::mirrorPixmapHorizontally(&rightPixmaps_[i]);
        upPixmaps_[i] = PixmapManager::rotatePixmap90DegreesCounterclockwise(&rightPixmaps_[i]);
        downPixmaps_[i] = PixmapManager::rotatePixmap90DegreesClockwise(&rightPixmaps_[i]);
    }
}
