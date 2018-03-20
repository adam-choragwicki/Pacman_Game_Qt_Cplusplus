#pragma once

#include <QtGui/QPixmap>
#include <array>

enum class Direction;

class AbstractGhostPixmapProvider
{
public:
    explicit AbstractGhostPixmapProvider(const std::array<QString, 6>& imageUrls);
    [[nodiscard]] virtual const QPixmap& getPixmap(Direction direction, int animationPhase) const;

    [[nodiscard]] const QPixmap& getScaredBluePixmap(int animationPhase) const;
    [[nodiscard]] const QPixmap& getScaredWhitePixmap(int animationPhase) const;

private:
    void initializePixmaps(const std::array<QString, 6>& imageUrls);
    static void initializeCommonPixmaps();

    static const int ANIMATION_PHASES_COUNT = 2;

    std::array<QPixmap, ANIMATION_PHASES_COUNT> leftPixmaps_;
    std::array<QPixmap, ANIMATION_PHASES_COUNT> rightPixmaps_;
    std::array<QPixmap, ANIMATION_PHASES_COUNT> upPixmaps_;
    std::array<QPixmap, ANIMATION_PHASES_COUNT> downPixmaps_;

    inline static std::unique_ptr<QPixmap> scaredBluePixmaps_[ANIMATION_PHASES_COUNT];
    inline static std::unique_ptr<QPixmap> scaredWhitePixmaps_[ANIMATION_PHASES_COUNT];

    inline static bool commonPixmapsInitialized_{};
};
