#pragma once

#include "game_map.h"
#include "pacman.h"
#include "ball_items_manager.h"
#include "ghosts/ghost_red.h"
#include "ghosts/ghost_purple.h"
#include "ghosts/ghost_blue.h"
#include "ghosts/ghost_orange.h"
#include "screen_text_display.h"
#include "score_display.h"

#include <memory>

class GameEngine : public QObject
{
    Q_OBJECT

signals:
    void restartGame();

public:
    GameEngine();
    ~GameEngine() override;
    void processKey(Key key);

private:
    enum class GameState
    {
        beforeFirstRun,
        gameRunning,
        gameStopped,
        gamePaused
    };

    void checkAndProcessCollisionWithGhost();
    void checkAndProcessCollisionWithFoodball();
    void checkAndProcessCollisionWithPowerball();
    void endGame(GameResult gameResult);
    void showGraphicsItems();
    void hideGraphicsItems();

    void startGame();
    void togglePause();

    static GameMap gameMap_;

    Pacman pacman_{gameMap_};
    GhostBlue ghostBlue_{gameMap_};
    GhostOrange ghostOrange_{gameMap_};
    GhostPurple ghostPurple_{gameMap_};
    GhostRed ghostRed_{gameMap_};

    std::array<MovableCharacterInterface*, 5> movableCharacters {};
    std::array<GhostBase*, 4> ghosts_ {};
    std::array<QGraphicsItem*, 6> graphicsItems_ {};

    ScreenTextDisplay screenTextDisplay_;

    ScoreDisplay scoreDisplay_;

    inline static GameState gameState_ = GameState::beforeFirstRun;

    QTimer gameTickTimer_;
    QTimer sceneUpdateTimer_;

    BallItemsManager ballItemsManager_;

    const std::chrono::milliseconds gameTickFrequency_ {30};
    const std::chrono::milliseconds sceneUpdateFrequency_ {16};

private slots:
    void gameTickHandler();
    void sceneUpdateHandler();
    void pacmanMovementHandler();
    void ghostMovementHandler(GhostBase* ghost);
};
