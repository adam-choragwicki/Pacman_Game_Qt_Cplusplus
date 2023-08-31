#pragma once

#include "movable_character.h"

class AbstractGhost : public MovableCharacter
{
public:
    AbstractGhost(const Coordinates& coordinates, Direction initialDirection);
    ~AbstractGhost() override = 0;

    void advanceAnimation() override;
    void reset() override;

    void resetScaredState()
    { scaredState_ = ScaredState::NO_SCARED; }

    void setScaredBlueState()
    { scaredState_ = ScaredState::SCARED_BLUE; }

    void setScaredWhiteState()
    { scaredState_ = ScaredState::SCARED_WHITE; }

    [[nodiscard]] bool isScared() const;
    [[nodiscard]] bool isScaredWhite() const;
    [[nodiscard]] bool isScaredBlue() const;

private:
    enum class ScaredState
    {
        NO_SCARED, SCARED_BLUE, SCARED_WHITE
    } scaredState_;
};
