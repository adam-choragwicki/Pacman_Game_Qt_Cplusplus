#pragma once

#include <QObject>
#include "common.h"

class GameLoop;

class GameStateManager : public QObject
{
Q_OBJECT

public slots:
    void processStartGameRequest();
    void processTogglePauseRequest();

public:
    explicit GameStateManager();
    void startGame();
    void endGame(GameResult gameResult);
    [[nodiscard]] bool isRunning() const;
    [[nodiscard]] bool isPaused() const;
    [[nodiscard]] bool isBeforeFirstRun() const;
    [[nodiscard]] bool isStopped() const;
    void togglePause();

    void transitionFromBeforeFirstRunToRunning();

    [[nodiscard]] const bool& getShouldDrawBackground() const;

    void setGameLoop(GameLoop* gameLoop)
    { gameLoop_ = gameLoop; }

    [[nodiscard]] bool isGameWin() const
    { return gameResult_ == GameResult::WIN; }

    [[nodiscard]] bool isGameLost() const
    { return gameResult_ == GameResult::LOST; }

private:
    bool shouldDrawBackground_{};

    enum class State
    {
        BEFORE_FIRST_RUN, RUNNING, STOPPED, PAUSED,
    } state_;

    GameLoop* gameLoop_{};

    GameResult gameResult_ = GameResult::NO_RESULT_YET;
};
