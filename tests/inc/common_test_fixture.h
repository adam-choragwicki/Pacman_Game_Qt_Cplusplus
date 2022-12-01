#pragma once

#include "gtest/gtest.h"
#include "game_map.h"

class CommonTestFixture : public ::testing::Test
{
protected:
    GameMap gameMap_;
};
