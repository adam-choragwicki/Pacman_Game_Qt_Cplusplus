#include "pacman_frontend.h"
#include "images_urls.h"
#include <QPainter>

PacmanFrontend::PacmanFrontend(const Pacman& pacman) : pacman_(pacman)
{
    loadImages(PacmanImages::IMAGES_URLS);
}

void PacmanFrontend::loadImages(const std::array<std::string, 16>& imagesUrls)
{
    const std::map<QPixmap*, std::string> pixmapToPathMapping{{&left1Pixmap_,  imagesUrls.at(0)},
                                                              {&left2Pixmap_,  imagesUrls.at(1)},
                                                              {&left3Pixmap_,  imagesUrls.at(2)},
                                                              {&left4Pixmap_,  imagesUrls.at(3)},

                                                              {&right1Pixmap_, imagesUrls.at(4)},
                                                              {&right2Pixmap_, imagesUrls.at(5)},
                                                              {&right3Pixmap_, imagesUrls.at(6)},
                                                              {&right4Pixmap_, imagesUrls.at(7)},

                                                              {&up1Pixmap_,    imagesUrls.at(8)},
                                                              {&up2Pixmap_,    imagesUrls.at(9)},
                                                              {&up3Pixmap_,    imagesUrls.at(10)},
                                                              {&up4Pixmap_,    imagesUrls.at(11)},

                                                              {&down1Pixmap_,  imagesUrls.at(12)},
                                                              {&down2Pixmap_,  imagesUrls.at(13)},
                                                              {&down3Pixmap_,  imagesUrls.at(14)},
                                                              {&down4Pixmap_,  imagesUrls.at(15)}};

    auto loadImage = [](const std::pair<QPixmap*, std::string>& pixmapToPathPair)
    {
        const auto&[pixmap, path] = pixmapToPathPair;
        return pixmap->load(QString::fromStdString(path));
    };

    if(!std::all_of(pixmapToPathMapping.cbegin(), pixmapToPathMapping.cend(), loadImage))
    {
        throw std::runtime_error("Error, cannot load pacman images");
    }
}

void PacmanFrontend::draw(QPainter& painter) const
{
    QRect boundingRect = pacman_.getRect();
    int animationState = pacman_.getAnimationState();

    switch(pacman_.getDirection())
    {
        case Direction::LEFT:
            if(animationState < 2 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, left1Pixmap_);
            }
            else if(animationState < 4 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, left2Pixmap_);
            }
            else if(animationState < 6 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, left3Pixmap_);
            }
            else if(animationState <= 8 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, left4Pixmap_);
            }
            break;

        case Direction::RIGHT:
            if(animationState < 2 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, right1Pixmap_);
            }
            else if(animationState < 4 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, right2Pixmap_);
            }
            else if(animationState < 6 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, right3Pixmap_);
            }
            else if(animationState <= 8 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, right4Pixmap_);
            }
            break;

        case Direction::UP:
            if(animationState < 2 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, up1Pixmap_);
            }
            else if(animationState < 4 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, up2Pixmap_);
            }
            else if(animationState < 6 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, up3Pixmap_);
            }
            else if(animationState <= 8 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, up4Pixmap_);
            }
            break;

        case Direction::DOWN:
            if(animationState < 2 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, down1Pixmap_);
            }
            else if(animationState < 4 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, down2Pixmap_);
            }
            else if(animationState < 6 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, down3Pixmap_);
            }
            else if(animationState <= 8 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, down4Pixmap_);
            }
            break;
    }
}
