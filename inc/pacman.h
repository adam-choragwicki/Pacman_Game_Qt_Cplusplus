#pragma once

#include "movable_character.h"

#include <QTimer>

class Pacman : public MovableCharacter
{
public:
    explicit Pacman(const GameMap& gameMap);
    ~Pacman() = default;

    QTimer& getMovementTimer()
    { return movementTimer_; }

    void reset() override;
    void startMovement() override;
    void stopMovement() override;

    void move();

private:
    void advanceAnimation() override;

    inline static const Coordinates STARTING_COORDINATES{320, 514};

    QTimer movementTimer_;

    const int animationSpeedFactor_ = 6;

    const std::chrono::milliseconds NORMAL_SPEED{6};
};
