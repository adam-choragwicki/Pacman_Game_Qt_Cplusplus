#pragma once

#include "movable_character.h"

class GhostTimingManager;

class AbstractGhost : public MovableCharacter
{
Q_OBJECT

public:
    AbstractGhost(const Coordinates& coordinates, Direction initialDirection, const std::chrono::seconds& moveOutOfTheStartingBoxTimeout, const std::array<QString, 8>& imagesUrls);
    ~AbstractGhost() override = 0;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void advanceAnimation() override;
    void reset() override;
    void respawn();

    void setScared();

    [[nodiscard]] bool isScared() const;

    [[nodiscard]] bool isSlowedDown() const
    { return isSlowedDown_; }

    [[nodiscard]] GhostTimingManager* getGhostTimingManager() const
    { return ghostTimingManager_.get(); }

protected:
    bool isSlowedDown_{};

private:
    static void initializeCommonPixmaps();
    void initializePixmaps(const std::array<QString, 8>& imagesUrls);

    enum class ScaredState
    {
        NO_SCARED, SCARED_BLUE, SCARED_WHITE
    } scaredState_;

    static const int ANIMATION_PHASES_COUNT = 2;

    QPixmap leftPixmaps_[ANIMATION_PHASES_COUNT];
    QPixmap rightPixmaps_[ANIMATION_PHASES_COUNT];
    QPixmap upPixmaps_[ANIMATION_PHASES_COUNT];
    QPixmap downPixmaps_[ANIMATION_PHASES_COUNT];

    inline static std::unique_ptr<QPixmap> scaredBluePixmaps_[ANIMATION_PHASES_COUNT];
    inline static std::unique_ptr<QPixmap> scaredWhitePixmaps_[ANIMATION_PHASES_COUNT];

    std::unique_ptr<GhostTimingManager> ghostTimingManager_;

    inline static bool commonPixmapsInitialized_{};

    /* Set higher to make animation slower */
    const int ANIMATION_SPEED_FACTOR = 30;
};
