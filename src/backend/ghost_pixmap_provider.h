#pragma once

#include "abstract_pixmap_provider.h"

class GhostPixmapProvider : public AbstractPixmapProvider
{
public:
    GhostPixmapProvider();

    [[nodiscard]] const QPixmap& getPixmap(Direction direction, int animationPhase) const override;
    [[nodiscard]] const QPixmap& getScaredBluePixmap(int animationPhase) const;
    [[nodiscard]] const QPixmap& getScaredWhitePixmap(int animationPhase) const;

private:
//    static void initializeCommonPixmaps();
    void initializePixmaps();

    static const int ANIMATION_PHASES_COUNT = 2;

    std::array<QPixmap, ANIMATION_PHASES_COUNT> leftPixmaps_;
    std::array<QPixmap, ANIMATION_PHASES_COUNT> rightPixmaps_;
    std::array<QPixmap, ANIMATION_PHASES_COUNT> upPixmaps_;
    std::array<QPixmap, ANIMATION_PHASES_COUNT> downPixmaps_;
    std::array<QPixmap, ANIMATION_PHASES_COUNT> scaredBluePixmaps_;
    std::array<QPixmap, ANIMATION_PHASES_COUNT> scaredWhitePixmaps_;
};
