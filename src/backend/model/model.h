#pragma once

class MovableCharacter;
class AbstractGhost;
class GhostTimingManager;
class AbstractTimingManager;
class BlueGhost;
class OrangeGhost;
class PurpleGhost;
class RedGhost;
class ScoreManager;
class GameStateManager;

class PacmanMovementManager;
class GhostMovementManager;

class QGraphicsScene;

class ScreenTextManager;
class ScreenTextDisplay;

class ScoreDisplay;

#include <map>
#include <memory>
#include "path_points.h"
#include "ball_items_manager.h"
#include "pacman.h"

#include "model/ghosts/blue_ghost.h"
#include "model/ghosts/orange_ghost.h"
#include "model/ghosts/purple_ghost.h"
#include "model/ghosts/red_ghost.h"

#include "screen_text_display.h"
#include "game_state_manager.h"
#include "ghost_timing_manager.h"

#include "pacman_movement_manager.h"
#include "ghost_movement_manager.h"

#include "balls/foodball.h"
#include "balls/powerball.h"
#include "score_display.h"

using AllCharactersContainer = std::array<MovableCharacter*, 5>;
using GhostsContainer = std::array<AbstractGhost*, 4>;
using AllTimingManagersContainer = std::array<AbstractTimingManager*, 5>;

class Model
{
public:
    Model();
    void reset();

    void initScene();

    [[nodiscard]] const Pacman& getPacman() const
    { return *pacman_; }

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

    [[nodiscard]] const ScoreManager& getScoreManager() const
    { return *scoreManager_; }

    [[nodiscard]] ScoreManager& getScoreManager()
    { return *scoreManager_; }

    [[nodiscard]] const ScreenTextManager& getScreenTextManager() const
    { return *screenTextManager_; }

    [[nodiscard]] ScreenTextManager& getScreenTextManager()
    { return *screenTextManager_; }

    [[nodiscard]] BallItemsManager& getBallItemsManager() const
    { return *ballItemsManager_; }

    [[nodiscard]] const GameStateManager& getGameStateManager() const
    { return *gameStateManager_; }

    GameStateManager& getGameStateManager()
    { return *gameStateManager_; }

    [[nodiscard]] std::map<AbstractGhost*, GhostTimingManager*>& getGhostToGhostTimingManagerMapping()
    { return ghostToGhostTimingManagerMapping_; }

    [[nodiscard]] const PathPoints& getPathPoints() const
    { return *pathPoints_; }

    [[nodiscard]] PacmanMovementManager& getPacmanMovementManager()
    { return *pacmanMovementManager_; }

    [[nodiscard]] GhostMovementManager& getGhostMovementManager()
    { return *ghostMovementManager_; }

    [[nodiscard]] QGraphicsScene* getScene() const
    { return scene_; }

    ScoreDisplay* scoreDisplay_{};

    //TODO this should not be here
    void startGame();
    void endGame(GameResult gameResult);

private:
    void addItemsToScene();
    void addBallsToScene();

    std::unique_ptr<PathPoints> pathPoints_;
    std::unique_ptr<BallItemsManager> ballItemsManager_;

    std::unique_ptr<Pacman> pacman_;
    std::unique_ptr<BlueGhost> blueGhost_;
    std::unique_ptr<OrangeGhost> orangeGhost_;
    std::unique_ptr<PurpleGhost> purpleGhost_;
    std::unique_ptr<RedGhost> redGhost_;

    std::unique_ptr<ScreenTextDisplay> screenTextDisplay_;

    ScoreManager* scoreManager_{};
    ScreenTextManager* screenTextManager_{};

    std::unique_ptr<GameStateManager> gameStateManager_;

    std::unique_ptr<GhostTimingManager> blueGhostTimingManager_;
    std::unique_ptr<GhostTimingManager> orangeGhostTimingManager_;
    std::unique_ptr<GhostTimingManager> purpleGhostTimingManager_;
    std::unique_ptr<GhostTimingManager> redGhostTimingManager_;

    std::map<AbstractGhost*, GhostTimingManager*> ghostToGhostTimingManagerMapping_;

    std::unique_ptr<PacmanMovementManager> pacmanMovementManager_;
    std::unique_ptr<GhostMovementManager> ghostMovementManager_;

    QGraphicsScene* scene_{};
};
