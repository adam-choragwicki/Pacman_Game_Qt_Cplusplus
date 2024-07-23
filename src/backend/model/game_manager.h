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

    [[nodiscard]] bool isRunning() const
    { return gameState_ == GameState::RUNNING; }

    [[nodiscard]] bool isPaused() const
    { return gameState_ == GameState::PAUSED; }

    [[nodiscard]] bool isReadyToStart() const
    { return gameState_ == GameState::READY_TO_START; }

    [[nodiscard]] bool isStopped() const
    { return gameState_ == GameState::STOPPED; }

    void togglePause();

    void prepareGameToStart();

    void setGameLoop(GameLoop* gameLoop)
    { gameLoop_ = gameLoop; }

    [[nodiscard]] bool isGameWin() const
    { return gameResult_ == GameResult::WIN; }

    [[nodiscard]] bool isGameLost() const
    { return gameResult_ == GameResult::LOST; }

private:
    void startGame();

    enum class GameState
    {
        READY_TO_START, RUNNING, PAUSED, STOPPED
    } gameState_;

    GameLoop* gameLoop_{};

    GameResult gameResult_ = GameResult::NO_RESULT_YET;

    Model& model_;
};
