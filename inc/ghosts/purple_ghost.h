#pragma once

#include "abstract_ghost.h"

class PurpleGhost : public AbstractGhost
{
public:
    explicit PurpleGhost(const GameMap& gameMap);
    ~PurpleGhost() override = default;

    void reset() override;

private:
    inline static const Coordinates STARTING_COORDINATES {307, 318};
    static constexpr std::chrono::seconds START_TIMEOUT {1};
};
