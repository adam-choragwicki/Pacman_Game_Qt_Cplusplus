#pragma once

class GameStateManager
{
public:
    explicit GameStateManager();
    void startGame();
    void endGame();
    [[nodiscard]] bool isRunning() const;
    [[nodiscard]] bool isPaused() const;
    [[nodiscard]] bool isBeforeFirstRun() const;
    [[nodiscard]] bool isStopped() const;
    void togglePause();

    void transitionFromBeforeFirstRunToRunning();

    [[nodiscard]] const bool& getShouldDrawBackground() const;

private:
    bool shouldDrawBackground_{};

    enum class State
    {
        BEFORE_FIRST_RUN, RUNNING, STOPPED, PAUSED,
    } state_;
};
