#pragma once

#include "pacman.h"
#include <QPixmap>

class PacmanFrontend
{
public:
    explicit PacmanFrontend();
    ~PacmanFrontend() = default;

    QPixmap left1Pixmap_, left2Pixmap_, left3Pixmap_, left4Pixmap_;
    QPixmap up1Pixmap_, up2Pixmap_, up3Pixmap_, up4Pixmap_;
    QPixmap down1Pixmap_, down2Pixmap_, down3Pixmap_, down4Pixmap_;
    QPixmap right1Pixmap_, right2Pixmap_, right3Pixmap_, right4Pixmap_;

    static const int ANIMATION_SPEED_FACTOR = 6;
    static const int DIAMETER = 30;

private:
    void loadImages();
};
