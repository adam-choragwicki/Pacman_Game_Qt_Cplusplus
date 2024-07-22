#pragma once

#include "path_points.h"
#include "ball_items_manager.h"
#include "pacman.h"

#include "model/ghosts/blue_ghost.h"
#include "model/ghosts/orange_ghost.h"
#include "model/ghosts/purple_ghost.h"
#include "model/ghosts/red_ghost.h"

#include "screen_text_display.h"
#include "game_state_manager.h"

#include "pacman_movement_manager.h"
#include "ghost_movement_manager.h"

#include "balls/foodball.h"
#include "balls/powerball.h"
#include "score_manager.h"
#include "score_display.h"

#include "game_loop.h"

#include <map>
#include <memory>
#include <QtWidgets/QGraphicsScene>

class MovableCharacter;
class AbstractGhost;
class BlueGhost;
class OrangeGhost;
class PurpleGhost;
class RedGhost;
class ScoreManager;
class GameStateManager;

class PacmanMovementManager;
class GhostMovementManager;

class ScreenTextManager;
class ScreenTextDisplay;

class ScoreDisplay;

class Model
{
public:
    Model();
    void reset();

    void initScene();

    [[nodiscard]] Pacman& getPacman()
    { return *pacman_; }

    [[nodiscard]] BlueGhost& getBlueGhost() const
    { return *blueGhost_; }

    [[nodiscard]] OrangeGhost& getOrangeGhost() const
    { return *orangeGhost_; }

    [[nodiscard]] PurpleGhost& getPurpleGhost() const
    { return *purpleGhost_; }

    [[nodiscard]] RedGhost& getRedGhost() const
    { return *redGhost_; }

    [[nodiscard]] ScoreManager& getScoreManager()
    { return *scoreManager_; }

    [[nodiscard]] BallItemsManager& getBallItemsManager() const
    { return *ballItemsManager_; }

    [[nodiscard]] const GameStateManager& getGameStateManager() const
    { return *gameStateManager_; }

    GameStateManager& getGameStateManager()
    { return *gameStateManager_; }

    [[nodiscard]] const PathPoints& getPathPoints() const
    { return *pathPoints_; }

    [[nodiscard]] PacmanMovementManager& getPacmanMovementManager()
    { return *pacmanMovementManager_; }

    [[nodiscard]] GhostMovementManager& getGhostMovementManager()
    { return *ghostMovementManager_; }

    [[nodiscard]] QGraphicsScene* getScene() const
    { return scene_.get(); }

    ScreenTextManager& getScreenTextManager()
    { return *screenTextManager_; }

private:
    void addItemsToScene();
    void addBallsToScene();

    std::unique_ptr<PathPoints> pathPoints_;

    std::unique_ptr<Pacman> pacman_;
    std::unique_ptr<BlueGhost> blueGhost_;
    std::unique_ptr<OrangeGhost> orangeGhost_;
    std::unique_ptr<PurpleGhost> purpleGhost_;
    std::unique_ptr<RedGhost> redGhost_;

    std::unique_ptr<ScoreManager> scoreManager_;
    std::unique_ptr<ScoreDisplay> scoreDisplay_;
    std::unique_ptr<ScreenTextManager> screenTextManager_;

    std::unique_ptr<PacmanMovementManager> pacmanMovementManager_;
    std::unique_ptr<GhostMovementManager> ghostMovementManager_;

    std::unique_ptr<GameLoop> gameLoop_;
    std::unique_ptr<GameStateManager> gameStateManager_;

    std::unique_ptr<QGraphicsScene> scene_;

    std::unique_ptr<ScreenTextDisplay> screenTextDisplay_;

    std::unique_ptr<BallItemsManager> ballItemsManager_;
};
