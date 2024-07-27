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

    QPixmap leftPixmaps_[ANIMATION_PHASES_COUNT];
    QPixmap rightPixmaps_[ANIMATION_PHASES_COUNT];
    QPixmap upPixmaps_[ANIMATION_PHASES_COUNT];
    QPixmap downPixmaps_[ANIMATION_PHASES_COUNT];

    /* Set higher to make animation slower */
    const int ANIMATION_SPEED_FACTOR = 10;
};
