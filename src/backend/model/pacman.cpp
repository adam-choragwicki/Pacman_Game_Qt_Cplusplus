#include "model/pacman.h"
#include "pixmap_loader.h"
#include "pixmap_manager.h"
#include <QtGui/QPainter>

Pacman::Pacman() : MovableCharacter(STARTING_COORDINATES, INITIAL_DIRECTION)
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

void Pacman::advanceAnimation()
{
    ++stepCounter_;

    if(stepCounter_ >= ANIMATION_SPEED_FACTOR)
    {
        stepCounter_ = 0;

        if(animationPhaseAscending_)
        {
            ++animationPhase_;
            if(animationPhase_ == ANIMATION_PHASES_COUNT - 1)
            {
                animationPhaseAscending_ = false;
            }
        }
        else
        {
            --animationPhase_;
            if(animationPhase_ == 0)
            {
                animationPhaseAscending_ = true;
            }
        }
    }
}

void Pacman::initializePixmaps()
{
    const std::vector<PixmapLoader::PixmapEntry> pixmapEntries = {{&rightPixmaps_[0], ":/pacman/pacman_right_close.png"},
                                                                  {&rightPixmaps_[1], ":/pacman/pacman_right_open_1.png"},
                                                                  {&rightPixmaps_[2], ":/pacman/pacman_right_open_2.png"},
                                                                  {&rightPixmaps_[3], ":/pacman/pacman_right_open_3.png"}};

    PixmapLoader::loadPixmaps(pixmapEntries);

    rightPixmaps_[0] = PixmapManager::scalePixmap(&rightPixmaps_[0], rect_);
    rightPixmaps_[1] = PixmapManager::scalePixmap(&rightPixmaps_[1], rect_);
    rightPixmaps_[2] = PixmapManager::scalePixmap(&rightPixmaps_[2], rect_);
    rightPixmaps_[3] = PixmapManager::scalePixmap(&rightPixmaps_[3], rect_);

    leftPixmaps_[0] = PixmapManager::mirrorPixmapHorizontally(&rightPixmaps_[0]);
    leftPixmaps_[1] = PixmapManager::mirrorPixmapHorizontally(&rightPixmaps_[1]);
    leftPixmaps_[2] = PixmapManager::mirrorPixmapHorizontally(&rightPixmaps_[2]);
    leftPixmaps_[3] = PixmapManager::mirrorPixmapHorizontally(&rightPixmaps_[3]);

    upPixmaps_[0] = PixmapManager::rotatePixmap90DegreesCounterclockwise(&rightPixmaps_[0]);
    upPixmaps_[1] = PixmapManager::rotatePixmap90DegreesCounterclockwise(&rightPixmaps_[1]);
    upPixmaps_[2] = PixmapManager::rotatePixmap90DegreesCounterclockwise(&rightPixmaps_[2]);
    upPixmaps_[3] = PixmapManager::rotatePixmap90DegreesCounterclockwise(&rightPixmaps_[3]);

    downPixmaps_[0] = PixmapManager::rotatePixmap90DegreesClockwise(&rightPixmaps_[0]);
    downPixmaps_[1] = PixmapManager::rotatePixmap90DegreesClockwise(&rightPixmaps_[1]);
    downPixmaps_[2] = PixmapManager::rotatePixmap90DegreesClockwise(&rightPixmaps_[2]);
    downPixmaps_[3] = PixmapManager::rotatePixmap90DegreesClockwise(&rightPixmaps_[3]);
}
