#pragma once

#include "abstract_ghost.h"

class RedGhost : public AbstractGhost
{
public:
    explicit RedGhost(const GameMap& gameMap);
    ~RedGhost() override = default;

    void reset() override;

private:
    inline static const Coordinates STARTING_COORDINATES{307, 252};
    inline static const Coordinates COORDINATES_AFTER_RESPAWN{307, 318};
    static constexpr std::chrono::seconds START_TIMEOUT{0};
};
