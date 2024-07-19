#pragma once

#include "abstract_timing_manager.h"

class PacmanTimingManager : public AbstractTimingManager
{
public:
    PacmanTimingManager();

    void startMovement() override;
    void stopMovement() override;
};
