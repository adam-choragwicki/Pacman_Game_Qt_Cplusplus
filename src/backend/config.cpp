#include "config.h"

using namespace std::chrono_literals;

Config::Config()
{
    worldMap.WORLD_HORIZONTAL_SQUARES_COUNT = 20;
    worldMap.WORLD_VERTICAL_SQUARES_COUNT = 20;
    worldMap.PRIMARY_SQUARE_SIZE = 30;
    calculateDerivedValues();
}

Config& Config::instance()
{
    if(!isInitialized_)
    {
        throw std::runtime_error("Config is not initialized. Call Config::initialize() first.");
    }

    return *instance_;
}

void Config::initialize()
{
    if(isInitialized_)
    {
        throw std::runtime_error("Config is already initialized.");
    }

    instance_ = new Config();
    isInitialized_ = true;
}

void Config::calculateDerivedValues()
{
    worldMap.WORLD_WIDTH = worldMap.WORLD_HORIZONTAL_SQUARES_COUNT * worldMap.PRIMARY_SQUARE_SIZE;
    worldMap.WORLD_HEIGHT = worldMap.WORLD_VERTICAL_SQUARES_COUNT * worldMap.PRIMARY_SQUARE_SIZE;

    worldMap.LEFT_BOUNDARY_X = 0;
    worldMap.RIGHT_BOUNDARY_X = worldMap.WORLD_WIDTH;
    worldMap.TOP_BOUNDARY_Y = 0;
    worldMap.BOTTOM_BOUNDARY_Y = worldMap.WORLD_HEIGHT;

    startingCoordinates.CHARACTER = Coordinates{static_cast<int>(0.5 * worldMap.WORLD_WIDTH), static_cast<int>(0.1 * worldMap.WORLD_HEIGHT)};
    startingCoordinates.CREATURE1 = Coordinates{static_cast<int>(0.5 * worldMap.WORLD_WIDTH), static_cast<int>(0.2 * worldMap.WORLD_HEIGHT)};
    startingCoordinates.CREATURE2 = Coordinates{static_cast<int>(0.4 * worldMap.WORLD_WIDTH), static_cast<int>(0.2 * worldMap.WORLD_HEIGHT)};
    startingCoordinates.CREATURE3 = Coordinates{static_cast<int>(0.6 * worldMap.WORLD_WIDTH), static_cast<int>(0.2 * worldMap.WORLD_HEIGHT)};

    startingCoordinates.BONELORD1 = Coordinates{static_cast<int>(0.3 * worldMap.WORLD_WIDTH), static_cast<int>(0.2 * worldMap.WORLD_HEIGHT)};
    startingCoordinates.BONELORD2 = Coordinates{static_cast<int>(0.7 * worldMap.WORLD_WIDTH), static_cast<int>(0.2 * worldMap.WORLD_HEIGHT)};

    startingCoordinates.BANSHEE = Coordinates{static_cast<int>(0.8 * worldMap.WORLD_WIDTH), static_cast<int>(0.2 * worldMap.WORLD_HEIGHT)};

    startingCoordinates.DEMON = Coordinates{static_cast<int>(0.2 * worldMap.WORLD_WIDTH), static_cast<int>(0.2 * worldMap.WORLD_HEIGHT)};

    physics.MINIMUM_DISPLACEMENT = 1;
    physics.MAX_HORIZONTAL_SPEED = 10;
    physics.AIR_FRICTION = 1;
    physics.ROPE_FRICTION = 1;
    physics.MAX_FALLING_SPEED = 10;
    physics.GRAVITY = 1;
    physics.JUMP_SPEED = -0.5 * worldMap.PRIMARY_SQUARE_SIZE;
    physics.NEGATIVE_MAX_ROPE_SPEED = physics.JUMP_SPEED / 2;
    physics.MAX_ROPE_SPEED = -physics.NEGATIVE_MAX_ROPE_SPEED;

    wall.WIDTH = worldMap.PRIMARY_SQUARE_SIZE;
    wall.HEIGHT = worldMap.PRIMARY_SQUARE_SIZE;

    platform.WIDTH = worldMap.PRIMARY_SQUARE_SIZE;
    platform.HEIGHT = worldMap.PRIMARY_SQUARE_SIZE / 5;

    rope.WIDTH = worldMap.PRIMARY_SQUARE_SIZE / 5;
    rope.HEIGHT = worldMap.PRIMARY_SQUARE_SIZE;
}
