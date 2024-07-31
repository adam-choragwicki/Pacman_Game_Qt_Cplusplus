#pragma once

#include <QtGui/QPixmap>

class ScaredGhostPixmapProvider
{
public:
    ScaredGhostPixmapProvider()
    {
        initializePixmaps();
    }

    [[nodiscard]] const QPixmap& getScaredBluePixmap(int animationPhase) const;
    [[nodiscard]] const QPixmap& getScaredWhitePixmap(int animationPhase) const;

private:
    static void initializePixmaps();

    static const int ANIMATION_PHASES_COUNT = 2;

    inline static std::unique_ptr<QPixmap> scaredBluePixmaps_[ANIMATION_PHASES_COUNT];
    inline static std::unique_ptr<QPixmap> scaredWhitePixmaps_[ANIMATION_PHASES_COUNT];
};
