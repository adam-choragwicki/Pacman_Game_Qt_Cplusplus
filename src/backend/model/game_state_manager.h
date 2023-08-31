#pragma once

class GameStateManager
{
    enum class State
    {
        BEFORE_FIRST_RUN, RUNNING, STOPPED, PAUSED,
    } state_;

public:
    explicit GameStateManager();
    void startGame();
    void endGame();
    [[nodiscard]] bool isRunning() const;
    [[nodiscard]] bool isPaused() const;
    [[nodiscard]] bool isBeforeFirstRun() const;
    [[nodiscard]] bool isStopped() const;
    void togglePause();
};
