#pragma once

#include <QtGui/QPixmap>
#include <array>

enum class Direction;

class AbstractGhostPixmapProvider
{
public:
    explicit AbstractGhostPixmapProvider(const std::array<QString, 6>& imageUrls);
    [[nodiscard]] virtual const QPixmap& getPixmap(Direction direction, int animationPhase) const;

private:
    void initializePixmaps(const std::array<QString, 6>& imageUrls);

    static const int ANIMATION_PHASES_COUNT = 2;

    std::array<QPixmap, ANIMATION_PHASES_COUNT> leftPixmaps_;
    std::array<QPixmap, ANIMATION_PHASES_COUNT> rightPixmaps_;
    std::array<QPixmap, ANIMATION_PHASES_COUNT> upPixmaps_;
    std::array<QPixmap, ANIMATION_PHASES_COUNT> downPixmaps_;
};
