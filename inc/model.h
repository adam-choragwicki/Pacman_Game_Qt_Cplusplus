#pragma once

#include "game_map.h"
#include "pacman.h"
#include "ball_items_manager.h"
#include "ghosts/red_ghost.h"
#include "ghosts/purple_ghost.h"
#include "ghosts/blue_ghost.h"
#include "ghosts/orange_ghost.h"

#include "score_manager.h"
#include "screen_text_manager.h"

#include <memory>

class Model : public QObject
{
Q_OBJECT

public:
    Model();
    ~Model() override = default;

    Pacman& getPacman()
    { return *pacman_; }

    BlueGhost& getBlueGhost()
    { return *blueGhost_; }

    OrangeGhost& getOrangeGhost()
    { return *orangeGhost_; }

    PurpleGhost& getPurpleGhost()
    { return *purpleGhost_; }

    RedGhost& getRedGhost()
    { return *redGhost_; }

    ScoreManager& getScoreManager()
    { return scoreManager_; }

    ScreenTextManager& getScreenTextManager()
    { return screenTextManager_; }

    BallItemsManager& getBallItemsManager()
    { return *ballItemsManager_; }

    GameState getGameState()
    { return gameState_; }

    void setGameState(GameState gameState)
    { gameState_ = gameState; }

    [[nodiscard]] const std::array<MovableCharacter*, 5>& getMovableCharacters() const
    { return movableCharacters; }

    void reset();

    [[nodiscard]] const std::array<AbstractGhost*, 4>& getGhosts() const
    { return ghosts_; }

private:
    GameState gameState_;

    std::unique_ptr<GameMap> gameMap_;
    std::unique_ptr<BallItemsManager> ballItemsManager_;

    std::unique_ptr<Pacman> pacman_;
    std::unique_ptr<BlueGhost> blueGhost_;
    std::unique_ptr<OrangeGhost> orangeGhost_;
    std::unique_ptr<PurpleGhost> purpleGhost_;
    std::unique_ptr<RedGhost> redGhost_;

    std::array<MovableCharacter*, 5> movableCharacters{};
    std::array<AbstractGhost*, 4> ghosts_{};

    ScoreManager scoreManager_;
    ScreenTextManager screenTextManager_;
};
