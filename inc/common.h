#pragma once

enum class Direction
{
    NONE, LEFT, UP, DOWN, RIGHT
};

enum class GameState
{
    BEFORE_FIRST_RUN, RUNNING, STOPPED, PAUSED
};

enum class GameResult
{
    NO_RESULT_YET, LOST, WIN
};

enum class Key
{
    LEFT, RIGHT, UP, DOWN, PAUSE, SPACE
};
