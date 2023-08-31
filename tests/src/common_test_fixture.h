#pragma once

#include "gtest/gtest.h"
#include "path_points.h"

class CommonTestFixture : public ::testing::Test
{
protected:
    PathPoints pathPoints_;
};
