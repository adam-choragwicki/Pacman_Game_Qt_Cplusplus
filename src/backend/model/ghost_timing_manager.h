#pragma once

#include "abstract_timing_manager.h"

class GhostTimingManager : public QObject, public AbstractTimingManager
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
