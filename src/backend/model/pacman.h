#pragma once

#include "movable_character.h"

class Pacman : public MovableCharacter
{
public:
    Pacman();
    void advanceAnimation() override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    void initializePixmaps();

    static const int ANIMATION_PHASES_COUNT = 4;

    std::array<QPixmap, ANIMATION_PHASES_COUNT> leftPixmaps_;
    std::array<QPixmap, ANIMATION_PHASES_COUNT> rightPixmaps_;
    std::array<QPixmap, ANIMATION_PHASES_COUNT> upPixmaps_;
    std::array<QPixmap, ANIMATION_PHASES_COUNT> downPixmaps_;

    /* Set higher to make animation slower */
    const int ANIMATION_SPEED_FACTOR = 10;

    inline static constexpr Direction INITIAL_DIRECTION{Direction::LEFT};
    inline static const Coordinates STARTING_COORDINATES{320, 514};
};
