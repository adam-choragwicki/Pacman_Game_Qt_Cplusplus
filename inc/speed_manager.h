#pragma once

#include <chrono>

class SpeedManager
{
public:

private:
    const std::chrono::milliseconds normalSpeed_{6};
    const std::chrono::milliseconds reducedSpeed_{50};
};
