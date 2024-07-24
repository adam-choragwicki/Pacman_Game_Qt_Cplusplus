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
    painter->setBrush(Qt::red);

    const QRect boundingRect = MovableCharacter::boundingRect().toRect();
    const int animationState = animationState_;

    //    QGraphicsEllipseItem asd;

    //        painter->setBrush(Qt::yellow);

    //    painter->drawEllipse(boundingRect);

    //        int multiplier = 16;

    //        painter->drawPie(boundingRect, 30 * multiplier, 300 * multiplier);

    //        painter->drawPie(boundingRect, 20 * multiplier, 320 * multiplier);
    //    painter->drawPie(boundingRect, 10 * multiplier, 340 * multiplier);


    switch(direction_)
    {
        case Direction::LEFT:
            if(animationState < 2 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter->drawPixmap(boundingRect, left1Pixmap_);
            }
            else if(animationState < 4 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter->drawPixmap(boundingRect, left2Pixmap_);
            }
            else if(animationState < 6 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter->drawPixmap(boundingRect, left3Pixmap_);
            }
            else if(animationState <= 8 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter->drawPixmap(boundingRect, left4Pixmap_);
            }
            break;

        case Direction::RIGHT:
            if(animationState < 2 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter->drawPixmap(boundingRect, right1Pixmap_);
            }
            else if(animationState < 4 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter->drawPixmap(boundingRect, right2Pixmap_);
            }
            else if(animationState < 6 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter->drawPixmap(boundingRect, right3Pixmap_);
            }
            else if(animationState <= 8 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter->drawPixmap(boundingRect, right4Pixmap_);
            }
            break;

        case Direction::UP:
            if(animationState < 2 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter->drawPixmap(boundingRect, up1Pixmap_);
            }
            else if(animationState < 4 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter->drawPixmap(boundingRect, up2Pixmap_);
            }
            else if(animationState < 6 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter->drawPixmap(boundingRect, up3Pixmap_);
            }
            else if(animationState <= 8 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter->drawPixmap(boundingRect, up4Pixmap_);
            }
            break;

        case Direction::DOWN:
            if(animationState < 2 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter->drawPixmap(boundingRect, down1Pixmap_);
            }
            else if(animationState < 4 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter->drawPixmap(boundingRect, down2Pixmap_);
            }
            else if(animationState < 6 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter->drawPixmap(boundingRect, down3Pixmap_);
            }
            else if(animationState <= 8 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter->drawPixmap(boundingRect, down4Pixmap_);
            }
            break;

        default:
            throw std::runtime_error("Cannot draw Pacman, wrong direction");
    }
}

void Pacman::advanceAnimation()
{
    if(animationState_ >= 8 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
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
