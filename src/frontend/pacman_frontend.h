#pragma once

#include "model/pacman.h"
#include <QPixmap>

class PacmanFrontend
{
public:
    explicit PacmanFrontend(const Pacman& pacman);
    ~PacmanFrontend() = default;

    QPixmap left1Pixmap_, left2Pixmap_, left3Pixmap_, left4Pixmap_;
    QPixmap up1Pixmap_, up2Pixmap_, up3Pixmap_, up4Pixmap_;
    QPixmap down1Pixmap_, down2Pixmap_, down3Pixmap_, down4Pixmap_;
    QPixmap right1Pixmap_, right2Pixmap_, right3Pixmap_, right4Pixmap_;

    void draw(QPainter& painter) const;

private:
    const Pacman& pacman_;

    void loadImages(const std::array<std::string, 16>& imagesUrls);
};
