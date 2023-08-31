#pragma once

#include "model/pacman.h"
#include "model/ghosts/abstract_ghost.h"
#include "timing_manager.h"
#include <QTimer>
#include <QObject>

class AbstractGhost;

class TimingManager
{
public:
    virtual void startMovement() = 0;
    virtual void stopMovement() = 0;

    [[nodiscard]] const QTimer& getMovementTimer() const
    { return movementTimer_; }

protected:
    QTimer movementTimer_;
};

class PacmanTimingManager : public TimingManager
{
public:
    PacmanTimingManager();

    void startMovement() override;
    void stopMovement() override;
};

class GhostTimingManager : public QObject, public TimingManager
{
Q_OBJECT

public:
    GhostTimingManager(AbstractGhost& abstractGhost, std::chrono::seconds startTimeout);
    void reset();

    void reduceSpeed();
    void startMovement() override;
    void stopMovement() override;

    void startScaredBlueTimer();

    [[nodiscard]] bool isItTimeToLeaveStartingBox() const
    { return timeToLeaveStartingBox_; }

private:
    QTimer scaredBlueStateTimer_;
    QTimer scaredWhiteStateTimer_;
    QTimer leaveStartingBoxTimer;

    AbstractGhost& ghost_;

    bool timeToLeaveStartingBox_{};

    void startScaredWhiteTimer();
    void resetSpeed();

private slots:
    void changeToScaredWhite();
    void changeToNoScared();
    void setLeaveStartingBox();
};
