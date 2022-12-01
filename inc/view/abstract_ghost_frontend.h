#pragma once

#include "ghosts/abstract_ghost.h"

#include <QPixmap>

class AbstractGhostFrontend
{
public:
    explicit AbstractGhostFrontend(AbstractGhost* abstractGhost);
    ~AbstractGhostFrontend() = default;

    QPixmap left1Pixmap_, left2Pixmap_, up1Pixmap_, up2Pixmap_, down1Pixmap_, down2Pixmap_, right1Pixmap_, right2Pixmap_;
    QPixmap scaredBlue1Pixmap_, scaredBlue2Pixmap_;
    QPixmap scaredWhite1Pixmap_, scaredWhite2Pixmap_;

    [[nodiscard]] AbstractGhost* getAbstractGhost() const
    { return abstractGhost_; }

    static const int DIAMETER = 30;

protected:
    void loadImages(const std::array<std::string, 12>& imagesUrls);

private:
    AbstractGhost* abstractGhost_;
};
