#pragma once

#include "movable_character.h"
#include "pixmap_providers/abstract_ghost_pixmap_provider.h"

class GhostTimingManager;

class AbstractGhost : public MovableCharacter
{
Q_OBJECT

public:
    AbstractGhost(const Coordinates& coordinates, Direction initialDirection, const std::chrono::seconds& moveOutOfTheStartingBoxTimeout, AbstractGhostPixmapProvider* pixmapProvider);
    ~AbstractGhost() override = 0;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

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
    enum class ScaredState
    {
        NO_SCARED, SCARED_BLUE, SCARED_WHITE
    } scaredState_;

    static const int ANIMATION_PHASES_COUNT = 2;

    /* Set higher to make animation slower */
    static const int ANIMATION_SPEED_FACTOR = 30;

    std::unique_ptr<GhostTimingManager> ghostTimingManager_;

    AbstractGhostPixmapProvider* pixmapProvider_{};
};
