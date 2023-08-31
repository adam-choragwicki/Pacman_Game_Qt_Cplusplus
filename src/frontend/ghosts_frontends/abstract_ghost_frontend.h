#pragma once

#include "model/ghosts/abstract_ghost.h"
#include "images_urls.h"
#include <QPixmap>

class AbstractGhostFrontend
{
public:
    explicit AbstractGhostFrontend(const AbstractGhost& ghost);
    ~AbstractGhostFrontend() = default;

    QPixmap left1Pixmap_, left2Pixmap_, up1Pixmap_, up2Pixmap_, down1Pixmap_, down2Pixmap_, right1Pixmap_, right2Pixmap_;
    QPixmap scaredBlue1Pixmap_, scaredBlue2Pixmap_;
    QPixmap scaredWhite1Pixmap_, scaredWhite2Pixmap_;

    void draw(QPainter& painter) const;

protected:
    void loadImages(const std::array<std::string, 12>& imagesUrls);

private:
    const AbstractGhost& ghost_;
};
