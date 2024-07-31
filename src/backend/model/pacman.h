#pragma once

#include "movable_character.h"

class PacmanPixmapProvider;

class Pacman : public MovableCharacter
{
public:
    explicit Pacman(PacmanPixmapProvider* pixmapProvider);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    static const int ANIMATION_PHASES_COUNT = 4;

    /* Set higher to make animation slower */
    static const int ANIMATION_SPEED_FACTOR = 10;

    inline static constexpr Direction INITIAL_DIRECTION{Direction::LEFT};
    inline static const Coordinates STARTING_COORDINATES{320, 514};

    PacmanPixmapProvider* pacmanPixmapProvider_{};
};
