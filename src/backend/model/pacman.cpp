#include "model/pacman.h"
#include "config.h"
#include "pixmap_loader.h"
#include <QtGui/QPainter>

Pacman::Pacman() : MovableCharacter(Config::StartingCoordinates::PACMAN, Config::InitialDirection::PACMAN)
{
    initializePixmaps();

    animationState_ = 0;
    direction_ = Direction::LEFT;

    drawRect_ = true;
}

void Pacman::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    CustomGraphicsItem::paint(painter, option, widget);

    painter->setRenderHint(QPainter::Antialiasing);

    const QPixmap* pixmap;
    const int animationPhase = animationState_ / Config::Timing::Pacman::ANIMATION_SPEED_FACTOR % 6;

//    qDebug() << "Animation phase: " << animationPhase << "       " << "Animation state: " << animationState_;;

    static const QPixmap* pixmaps[4][6] = {{&left1Pixmap_,  &left2Pixmap_,  &left3Pixmap_,  &left4Pixmap_,  &left3Pixmap_,  &left2Pixmap_}, // LEFT
                                           {&right1Pixmap_, &right2Pixmap_, &right3Pixmap_, &right4Pixmap_, &right3Pixmap_, &right2Pixmap_}, // RIGHT
                                           {&up1Pixmap_,    &up2Pixmap_,    &up3Pixmap_,    &up4Pixmap_,    &up3Pixmap_,    &up2Pixmap_}, // UP
                                           {&down1Pixmap_,  &down2Pixmap_,  &down3Pixmap_,  &down4Pixmap_,  &down3Pixmap_,  &down2Pixmap_} // DOWN
    };

    switch(direction_)
    {
        case Direction::LEFT:
            pixmap = pixmaps[0][animationPhase];
            break;
        case Direction::RIGHT:
            pixmap = pixmaps[1][animationPhase];
            break;
        case Direction::UP:
            pixmap = pixmaps[2][animationPhase];
            break;
        case Direction::DOWN:
            pixmap = pixmaps[3][animationPhase];
            break;
        default:
            throw std::runtime_error("Cannot draw Pacman, wrong direction");
    }

    painter->setPen(Qt::NoPen);

    /* This is required to avoid artifacts */
    const qreal penWidth = painter->pen().widthF();
    const QRectF targetRect = rect_.adjusted(penWidth / 2, penWidth / 2, -penWidth / 2, -penWidth / 2);
    painter->drawPixmap(targetRect.toRect(), *pixmap);
}

void Pacman::advanceAnimation()
{
    if(animationState_ >= 14 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
    {
        animationState_ = 0;
    }
    else
    {
        ++animationState_;
    }
}

void Pacman::initializePixmaps()
{
    const std::vector<PixmapLoader::PixmapEntry> pixmapEntries = {{&right1Pixmap_, ":/pacman/pacman_right_close.png"},
                                                                  {&right2Pixmap_, ":/pacman/pacman_right_open_1.png"},
                                                                  {&right3Pixmap_, ":/pacman/pacman_right_open_2.png"},
                                                                  {&right4Pixmap_, ":/pacman/pacman_right_open_3.png"}};

    PixmapLoader::loadPixmaps(pixmapEntries);

    qDebug() << "Original size: " << right1Pixmap_.size();
    qDebug() << "Original size: " << right2Pixmap_.size();
    qDebug() << "Original size: " << right3Pixmap_.size();
    qDebug() << "Original size: " << right4Pixmap_.size();

    right1Pixmap_ = right1Pixmap_.scaled(static_cast<int>(rect_.width()), static_cast<int>(rect_.height()), Qt::AspectRatioMode::IgnoreAspectRatio, Qt::TransformationMode::SmoothTransformation);
    right2Pixmap_ = right2Pixmap_.scaled(static_cast<int>(rect_.width()), static_cast<int>(rect_.height()), Qt::AspectRatioMode::IgnoreAspectRatio, Qt::TransformationMode::SmoothTransformation);
    right3Pixmap_ = right3Pixmap_.scaled(static_cast<int>(rect_.width()), static_cast<int>(rect_.height()), Qt::AspectRatioMode::IgnoreAspectRatio, Qt::TransformationMode::SmoothTransformation);
    right4Pixmap_ = right4Pixmap_.scaled(static_cast<int>(rect_.width()), static_cast<int>(rect_.height()), Qt::AspectRatioMode::IgnoreAspectRatio, Qt::TransformationMode::SmoothTransformation);

    qDebug() << "After scaling: " << right1Pixmap_.size();
    qDebug() << "After scaling: " << right2Pixmap_.size();
    qDebug() << "After scaling: " << right3Pixmap_.size();
    qDebug() << "After scaling: " << right4Pixmap_.size();

    QTransform verticalMirrorTransformation;
    verticalMirrorTransformation.scale(-1, +1);

    left1Pixmap_ = right1Pixmap_.transformed(verticalMirrorTransformation, Qt::TransformationMode::SmoothTransformation);
    left2Pixmap_ = right2Pixmap_.transformed(verticalMirrorTransformation, Qt::TransformationMode::SmoothTransformation);
    left3Pixmap_ = right3Pixmap_.transformed(verticalMirrorTransformation, Qt::TransformationMode::SmoothTransformation);
    left4Pixmap_ = right4Pixmap_.transformed(verticalMirrorTransformation, Qt::TransformationMode::SmoothTransformation);

    QTransform rotate90DegreesCounterclockwise;
    rotate90DegreesCounterclockwise.rotate(-90);

    up1Pixmap_ = right1Pixmap_.transformed(rotate90DegreesCounterclockwise, Qt::TransformationMode::SmoothTransformation);
    up2Pixmap_ = right2Pixmap_.transformed(rotate90DegreesCounterclockwise, Qt::TransformationMode::SmoothTransformation);
    up3Pixmap_ = right3Pixmap_.transformed(rotate90DegreesCounterclockwise, Qt::TransformationMode::SmoothTransformation);
    up4Pixmap_ = right4Pixmap_.transformed(rotate90DegreesCounterclockwise, Qt::TransformationMode::SmoothTransformation);

    QTransform rotate90DegreesClockwise;
    rotate90DegreesClockwise.rotate(+90);

    down1Pixmap_ = right1Pixmap_.transformed(rotate90DegreesClockwise, Qt::TransformationMode::SmoothTransformation);
    down2Pixmap_ = right2Pixmap_.transformed(rotate90DegreesClockwise, Qt::TransformationMode::SmoothTransformation);
    down3Pixmap_ = right3Pixmap_.transformed(rotate90DegreesClockwise, Qt::TransformationMode::SmoothTransformation);
    down4Pixmap_ = right4Pixmap_.transformed(rotate90DegreesClockwise, Qt::TransformationMode::SmoothTransformation);
}
