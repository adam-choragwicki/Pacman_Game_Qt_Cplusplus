#pragma once

#include "gtest/gtest.h"
#include "game_map.h"
#include "drawer.h"

#include <QGraphicsScene>

class CommonTestFixture : public ::testing::Test
{
public:
    CommonTestFixture()
    {
        Drawer::setScene(&scene_);
    }

protected:
    QGraphicsScene scene_;
    GameMap gameMap_;
};
