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

    //    QGraphicsEllipseItem asd;

    //        painter->setBrush(Qt::yellow);

    //    painter->drawEllipse(boundingRect);

    //        int multiplier = 16;

    //        painter->drawPie(boundingRect, 30 * multiplier, 300 * multiplier);

    //        painter->drawPie(boundingRect, 20 * multiplier, 320 * multiplier);
    //    painter->drawPie(boundingRect, 10 * multiplier, 340 * multiplier);

    QPixmap* pixmap{};

    switch(direction_)
    {
        case Direction::LEFT:
            if(animationState_ < 2 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                pixmap = &left1Pixmap_;
            }
            else if(animationState_ < 4 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                pixmap = &left2Pixmap_;
            }
            else if(animationState_ < 6 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                pixmap = &left3Pixmap_;
            }
            else
            {
                pixmap = &left4Pixmap_;
            }
            break;

        case Direction::RIGHT:
            if(animationState_ < 2 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                pixmap = &right1Pixmap_;
            }
            else if(animationState_ < 4 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                pixmap = &right2Pixmap_;
            }
            else if(animationState_ < 6 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                pixmap = &right3Pixmap_;
            }
            else
            {
                pixmap = &right4Pixmap_;
            }
            break;

        case Direction::UP:
            if(animationState_ < 2 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                pixmap = &up1Pixmap_;
            }
            else if(animationState_ < 4 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                pixmap = &up2Pixmap_;
            }
            else if(animationState_ < 6 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                pixmap = &up3Pixmap_;
            }
            else
            {
                pixmap = &up4Pixmap_;
            }
            break;

        case Direction::DOWN:
            if(animationState_ < 2 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                pixmap = &down1Pixmap_;
            }
            else if(animationState_ < 4 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                pixmap = &down2Pixmap_;
            }
            else if(animationState_ < 6 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                pixmap = &down3Pixmap_;
            }
            else
            {
                pixmap = &down4Pixmap_;
            }
            break;

        default:
            throw std::runtime_error("Cannot draw Pacman, wrong direction");
    }

    painter->drawPixmap(rect_.toRect(), *pixmap);
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
