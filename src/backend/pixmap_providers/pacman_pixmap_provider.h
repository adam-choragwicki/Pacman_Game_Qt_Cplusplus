#pragma once

#include <array>
#include <vector>
#include <QtGui/QPixmap>
#include "common.h"

class PacmanPixmapProvider
{
public:
    PacmanPixmapProvider();

    [[nodiscard]] const QPixmap& getPixmap(Direction direction, int animationPhase) const;

private:
    void initializePixmaps();

    static const int ANIMATION_PHASES_COUNT = 4;

    std::array<QPixmap, ANIMATION_PHASES_COUNT> leftPixmaps_;
    std::array<QPixmap, ANIMATION_PHASES_COUNT> rightPixmaps_;
    std::array<QPixmap, ANIMATION_PHASES_COUNT> upPixmaps_;
    std::array<QPixmap, ANIMATION_PHASES_COUNT> downPixmaps_;
};
