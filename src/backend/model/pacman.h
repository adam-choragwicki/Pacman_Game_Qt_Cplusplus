#pragma once

#include "movable_character.h"

class Pacman : public MovableCharacter
{
public:
    Pacman();
    void advanceAnimation() override;
};
