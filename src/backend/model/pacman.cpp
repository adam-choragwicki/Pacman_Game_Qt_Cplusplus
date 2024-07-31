#include "model/pacman.h"
#include "pixmap_loader.h"
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

    const QPixmap* pixmap{};

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

    const double penWidth = painter->pen().widthF();
    const QRectF targetRect = rect_.adjusted(penWidth / 2, penWidth / 2, -penWidth / 2, -penWidth / 2);
    painter->drawPixmap(targetRect.toRect(), *pixmap);
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

    rightPixmaps_[0] = rightPixmaps_[0].scaled(static_cast<int>(rect_.width()), static_cast<int>(rect_.height()), Qt::AspectRatioMode::IgnoreAspectRatio, Qt::TransformationMode::SmoothTransformation);
    rightPixmaps_[1] = rightPixmaps_[1].scaled(static_cast<int>(rect_.width()), static_cast<int>(rect_.height()), Qt::AspectRatioMode::IgnoreAspectRatio, Qt::TransformationMode::SmoothTransformation);
    rightPixmaps_[2] = rightPixmaps_[2].scaled(static_cast<int>(rect_.width()), static_cast<int>(rect_.height()), Qt::AspectRatioMode::IgnoreAspectRatio, Qt::TransformationMode::SmoothTransformation);
    rightPixmaps_[3] = rightPixmaps_[3].scaled(static_cast<int>(rect_.width()), static_cast<int>(rect_.height()), Qt::AspectRatioMode::IgnoreAspectRatio, Qt::TransformationMode::SmoothTransformation);

    QTransform verticalMirrorTransformation;
    verticalMirrorTransformation.scale(-1, +1);

    leftPixmaps_[0] = rightPixmaps_[0].transformed(verticalMirrorTransformation, Qt::TransformationMode::SmoothTransformation);
    leftPixmaps_[1] = rightPixmaps_[1].transformed(verticalMirrorTransformation, Qt::TransformationMode::SmoothTransformation);
    leftPixmaps_[2] = rightPixmaps_[2].transformed(verticalMirrorTransformation, Qt::TransformationMode::SmoothTransformation);
    leftPixmaps_[3] = rightPixmaps_[3].transformed(verticalMirrorTransformation, Qt::TransformationMode::SmoothTransformation);

    QTransform rotate90DegreesCounterclockwise;
    rotate90DegreesCounterclockwise.rotate(-90);

    upPixmaps_[0] = rightPixmaps_[0].transformed(rotate90DegreesCounterclockwise, Qt::TransformationMode::SmoothTransformation);
    upPixmaps_[1] = rightPixmaps_[1].transformed(rotate90DegreesCounterclockwise, Qt::TransformationMode::SmoothTransformation);
    upPixmaps_[2] = rightPixmaps_[2].transformed(rotate90DegreesCounterclockwise, Qt::TransformationMode::SmoothTransformation);
    upPixmaps_[3] = rightPixmaps_[3].transformed(rotate90DegreesCounterclockwise, Qt::TransformationMode::SmoothTransformation);

    QTransform rotate90DegreesClockwise;
    rotate90DegreesClockwise.rotate(+90);

    downPixmaps_[0] = rightPixmaps_[0].transformed(rotate90DegreesClockwise, Qt::TransformationMode::SmoothTransformation);
    downPixmaps_[1] = rightPixmaps_[1].transformed(rotate90DegreesClockwise, Qt::TransformationMode::SmoothTransformation);
    downPixmaps_[2] = rightPixmaps_[2].transformed(rotate90DegreesClockwise, Qt::TransformationMode::SmoothTransformation);
    downPixmaps_[3] = rightPixmaps_[3].transformed(rotate90DegreesClockwise, Qt::TransformationMode::SmoothTransformation);
}
