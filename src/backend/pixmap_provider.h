#pragma once

#include "abstract_pixmap_provider.h"
#include <array>
#include <vector>

class PixmapProvider : public AbstractPixmapProvider
{
public:
    PixmapProvider();

    [[nodiscard]] QPixmap getPixmap(Direction direction, int animationPhase) const override;

private:
    void initializePixmaps();

    static const int ANIMATION_PHASES_COUNT = 4;

    std::array<QPixmap, ANIMATION_PHASES_COUNT> leftPixmaps_;
    std::array<QPixmap, ANIMATION_PHASES_COUNT> rightPixmaps_;
    std::array<QPixmap, ANIMATION_PHASES_COUNT> upPixmaps_;
    std::array<QPixmap, ANIMATION_PHASES_COUNT> downPixmaps_;
};
