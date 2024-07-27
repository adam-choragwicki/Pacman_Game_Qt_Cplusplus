#pragma once

#include <chrono>
#include "coordinates.h"
#include "common.h"

namespace Config
{
    namespace Timing
    {
        using namespace std::chrono_literals;

        /*Approximately 60Hz refresh rate*/
        static constexpr auto VIEWPORT_UPDATE_INTERVAL = 17ms;

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
            const auto SCARED_BLUE_TIME = 1s;
            const auto SCARED_WHITE_TIME = 1s;
        }

        static const auto GAME_LOOP_INTERVAL = MovableCharacter::NORMAL_SPEED;
    }
}
