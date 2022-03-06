#pragma once

#include "game_map.h"
#include "pacman.h"
#include "powerball.h"
#include "foodball.h"
#include "ghost_red.h"
#include "ghost_purple.h"
#include "ghost_blue.h"
#include "ghost_orange.h"
#include "screen_text_display.h"
#include "score_display.h"

class GameEngine : public QObject
{
    Q_OBJECT

public:
    GameEngine();
    void processKey(QString key);

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
    void drawGraphicsItems();
    void endGame(GameResult gameResult);
    void showGraphicsItems();
    void hideGraphicsItems();
    void populateMapWithBalls();
    void removeBalls();
    void startGame();
    void togglePause();

    GameMap gameMap_;
    Pacman pacman_;
    GhostBlue ghostBlue_;
    GhostOrange ghostOrange_;
    GhostPurple ghostPurple_;
    GhostRed ghostRed_;

    std::array<MovableCharacterInterface*, 5> movableCharacters {&pacman_, &ghostBlue_, &ghostOrange_, &ghostPurple_, &ghostRed_};
    std::array<GhostBase*, 4> ghosts_ {&ghostBlue_, &ghostOrange_, &ghostPurple_, &ghostRed_};
    std::array<QGraphicsItem*, 6> graphicsItems_ {&pacman_, &ghostBlue_, &ghostOrange_, &ghostPurple_, &ghostRed_, &scoreDisplay_};

    ScreenTextDisplay screenTextDisplay_;
    ScoreDisplay scoreDisplay_;

    GameState gameState_;

    QTimer gameTickTimer_;
    QTimer sceneUpdateTimer_;

    std::vector<std::unique_ptr<Foodball>> foodballGraphicsItems_;
    std::vector<std::unique_ptr<Powerball>> powerballGraphicsItems_;

    const int gameTickFrequency_ = 30; /* 4 milliseconds */
    const int sceneUpdateFrequency_ = 16; /* 16 milliseconds is enough for 60Hz display */

private slots:
    void gameTickHandler();
    void sceneUpdateHandler();
    void pacmanMovementHandler();
    void ghostMovementHandler(GhostBase* ghost);
};
