#pragma once

#include <chrono>
#include "coordinates.h"
#include "common.h"

namespace Config
{
    namespace Timing
    {
        using namespace std::chrono_literals;
        static constexpr auto VIEWPORT_UPDATE_INTERVAL = 16ms;

        namespace MovableCharacter
        {
            const auto NORMAL_SPEED = 6ms;
        }

        namespace Pacman
        {
            const auto ANIMATION_SPEED_FACTOR = 6;
        }

        namespace Ghost
        {
            const auto REDUCED_SPEED = 50ms;
            const auto SCARED_BLUE_TIME = 4s;
            const auto SCARED_WHITE_TIME = 2s;
        }

        static const auto TICK_INTERVAL = MovableCharacter::NORMAL_SPEED;
    }

    namespace InitialDirection
    {
        const Direction PACMAN = Direction::LEFT;
        const Direction BLUE_GHOST = Direction::UP;
        const Direction ORANGE_GHOST = Direction::UP;
        const Direction PURPLE_GHOST = Direction::UP;
        const Direction RED_GHOST = Direction::LEFT;
    }

    namespace Foodball
    {
        const int DIAMETER = 7;
    }

    namespace Powerball
    {
        const int DIAMETER = 15;
    }

    namespace StartingCoordinates
    {
        const Coordinates PACMAN{320, 514};
        const Coordinates BLUE_GHOST{265, 318};
        const Coordinates ORANGE_GHOST{349, 318};
        const Coordinates PURPLE_GHOST{307, 318};
        const Coordinates RED_GHOST{307, 252};
    }

    namespace StartTimeout
    {
        using namespace std::chrono_literals;

        const auto BLUE_GHOST = 3s;
        const auto ORANGE_GHOST = 2s;
        const auto PURPLE_GHOST = 1s;
        const auto RED_GHOST = 0s;
    }
}
