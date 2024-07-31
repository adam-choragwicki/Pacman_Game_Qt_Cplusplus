#pragma once

#include "coordinates.h"
#include <chrono>

using namespace std::chrono_literals;

class Config
{
public:
    Config();

    struct Timing
    {
        static constexpr auto TICK_INTERVAL = 16ms;
        static constexpr auto INPUT_CAPTURE_INTERVAL = 12ms;
        static constexpr auto VIEWPORT_UPDATE_INTERVAL = 16ms;
    };

    struct WorldMap
    {
        int WORLD_HORIZONTAL_SQUARES_COUNT;
        int WORLD_VERTICAL_SQUARES_COUNT;

        int PRIMARY_SQUARE_SIZE;

        int WORLD_WIDTH;
        int WORLD_HEIGHT;

        int LEFT_BOUNDARY_X;
        int RIGHT_BOUNDARY_X;
        int TOP_BOUNDARY_Y;
        int BOTTOM_BOUNDARY_Y;
    };

    struct StartingCoordinates
    {
        Coordinates CHARACTER{0, 0};
        Coordinates CREATURE1{0, 0};
        Coordinates CREATURE2{0, 0};
        Coordinates CREATURE3{0, 0};

        Coordinates BONELORD1{0, 0};
        Coordinates BONELORD2{0, 0};

        Coordinates BANSHEE{0, 0};

        Coordinates DEMON{0, 0};
    };

    struct Wall
    {
        int WIDTH;
        int HEIGHT;
    };

    struct Platform
    {
        int WIDTH;
        int HEIGHT;
    };

    struct Rope
    {
        int WIDTH;
        int HEIGHT;
    };

    struct Physics
    {
        double MINIMUM_DISPLACEMENT;

        double MAX_HORIZONTAL_SPEED;
        double AIR_FRICTION;
        double ROPE_FRICTION;

        double MAX_FALLING_SPEED;

        double GRAVITY;

        double JUMP_SPEED;

        double NEGATIVE_MAX_ROPE_SPEED;
        double MAX_ROPE_SPEED;
    };

    static Config& instance();
    static void initialize();

    Timing timing;
    WorldMap worldMap;
    StartingCoordinates startingCoordinates;
    Physics physics;
    Wall wall;
    Platform platform;
    Rope rope;

private:
    void calculateDerivedValues();

    // Define the static members
    inline static Config* instance_ = nullptr;
    inline static bool isInitialized_ = false;
};
