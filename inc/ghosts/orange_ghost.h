#pragma once

#include "abstract_ghost.h"

class OrangeGhost : public AbstractGhost
{
public:
    explicit OrangeGhost(const GameMap& gameMap);
    ~OrangeGhost() override = default;

    void reset() override;

private:
    inline static const Coordinates STARTING_COORDINATES {349, 318};
    static constexpr std::chrono::seconds START_TIMEOUT{2};
};
