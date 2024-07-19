#pragma once

#include "model/pacman.h"
#include "model/ghosts/abstract_ghost.h"
#include "abstract_timing_manager.h"
#include <QTimer>
#include <QObject>

class AbstractGhost;

class AbstractTimingManager
{
public:
    virtual void startMovement() = 0;
    virtual void stopMovement() = 0;
};
