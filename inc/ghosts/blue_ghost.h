#pragma once

#include "abstract_ghost.h"

class BlueGhost : public AbstractGhost
{
public:
    explicit BlueGhost(const GameMap& gameMap);
    ~BlueGhost() override = default;

    void reset() override;

private:
    inline static const Coordinates STARTING_COORDINATES {265, 318};
    static constexpr std::chrono::seconds START_TIMEOUT{3};
};
