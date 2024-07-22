#pragma once

#include <QObject>
#include "common.h"
class Model;

class GameLoop;

class GameManager : public QObject
{
Q_OBJECT

public slots:
    void processStartOrRestartGameRequest();
    void processTogglePauseRequest();

    void endGame(GameResult gameResult);

public:
    explicit GameManager(Model& model);
    [[nodiscard]] bool isRunning() const;
    [[nodiscard]] bool isPaused() const;
    [[nodiscard]] bool isReadyToStart() const;
    [[nodiscard]] bool isStopped() const;
    void togglePause();

    [[nodiscard]] const bool& getShouldDrawBackground() const;

    void setGameLoop(GameLoop* gameLoop)
    { gameLoop_ = gameLoop; }

    [[nodiscard]] bool isGameWin() const
    { return gameResult_ == GameResult::WIN; }

    [[nodiscard]] bool isGameLost() const
    { return gameResult_ == GameResult::LOST; }

private:
    void startGame();

    bool shouldDrawBackground_{};

    enum class GameState
    {
        READY_TO_START, RUNNING, PAUSED, STOPPED
    } gameState_;

    GameLoop* gameLoop_{};

    GameResult gameResult_ = GameResult::NO_RESULT_YET;
    void prepareGameToStart();

    Model& model_;
};
