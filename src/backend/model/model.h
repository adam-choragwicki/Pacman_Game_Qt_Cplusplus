#pragma once

#include "path_points.h"
#include "pellets_manager.h"

#include "pacman.h"
#include "ghosts/blue_ghost.h"
#include "ghosts/orange_ghost.h"
#include "ghosts/purple_ghost.h"
#include "ghosts/red_ghost.h"

#include "pacman_movement_manager.h"
#include "ghost_movement_manager.h"

#include "pellets/standard_pellet.h"
#include "pellets/power_pellet.h"

#include "screen_text_display.h"
#include "score_manager.h"
#include "score_display.h"

#include "what_to_draw_manager.h"

#include "graphics_scene.h"
#include "pacman_pixmap_provider.h"
#include "ghost_pixmap_provider.h"

class Model
{
public:
    Model();
    void reset();

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

    [[nodiscard]] PelletsManager& getPelletsManager() const
    { return *pelletsManager_; }

    [[nodiscard]] const PathPoints& getPathPoints() const
    { return *pathPoints_; }

    [[nodiscard]] PacmanMovementManager& getPacmanMovementManager()
    { return *pacmanMovementManager_; }

    [[nodiscard]] GhostMovementManager& getGhostMovementManager()
    { return *ghostMovementManager_; }

    [[nodiscard]] GraphicsScene* getScene() const
    { return scene_.get(); }

    [[nodiscard]] ScreenTextDisplay* getScreenTextDisplay() const
    { return screenTextDisplay_.get(); }

    [[nodiscard]] WhatToDrawManager* getWhatToDrawManager() const
    { return whatToDrawManager_.get(); }

    [[nodiscard]] ScoreDisplay* getScoreDisplay() const
    { return scoreDisplay_.get(); }

private:
    void addItemsToScene();
    void addPelletsToScene();

    std::unique_ptr<GraphicsScene> scene_;

    std::unique_ptr<PathPoints> pathPoints_;

    std::unique_ptr<PacmanPixmapProvider> pacmanPixmapProvider_;
    std::shared_ptr<GhostPixmapProvider> ghostPixmapProvider_;

    std::unique_ptr<Pacman> pacman_;
    std::unique_ptr<BlueGhost> blueGhost_;
    std::unique_ptr<OrangeGhost> orangeGhost_;
    std::unique_ptr<PurpleGhost> purpleGhost_;
    std::unique_ptr<RedGhost> redGhost_;

    std::unique_ptr<ScoreManager> scoreManager_;
    std::unique_ptr<ScoreDisplay> scoreDisplay_;

    std::unique_ptr<PacmanMovementManager> pacmanMovementManager_;
    std::unique_ptr<GhostMovementManager> ghostMovementManager_;

    std::unique_ptr<ScreenTextDisplay> screenTextDisplay_;

    std::unique_ptr<PelletsManager> pelletsManager_;

    std::unique_ptr<WhatToDrawManager> whatToDrawManager_;
};
