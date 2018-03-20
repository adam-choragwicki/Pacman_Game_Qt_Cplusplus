#pragma once

#include <QObject>
#include <QTimer>

class GhostTimingManager : public QObject
{
Q_OBJECT

public:
    explicit GhostTimingManager(const std::chrono::seconds& moveOutOfTheStartingBoxTimeout);
    void reset();

    void startLeaveStartingBoxTimer();

    void startScaredBlueTimer();
    void startScaredWhiteTimer();

    [[nodiscard]] bool isItTimeToLeaveStartingBox() const
    { return timeToLeaveStartingBox_; }

    void setTimeToLeaveStartingBox()
    { timeToLeaveStartingBox_ = true; }

    [[nodiscard]] const QTimer& getScaredBlueStateTimer() const
    { return scaredBlueStateTimer_; }

    [[nodiscard]] const QTimer& getScaredWhiteStateTimer() const
    { return scaredWhiteStateTimer_; }

private:
    static constexpr auto SCARED_BLUE_TIME = std::chrono::seconds(3);
    static constexpr auto SCARED_WHITE_TIME = std::chrono::seconds(1);

    QTimer scaredBlueStateTimer_;
    QTimer scaredWhiteStateTimer_;
    QTimer timeToLeaveStartingBoxTimer;

    bool timeToLeaveStartingBox_{};

    void initializeTimers(const std::chrono::seconds& moveOutOfTheStartingBoxTimeout);
};
