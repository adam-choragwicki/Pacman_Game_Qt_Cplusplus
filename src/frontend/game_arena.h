#pragma once

#include "model/model.h"

#include "pacman_frontend.h"
#include "ghosts_frontends/blue_ghost_frontend.h"
#include "ghosts_frontends/orange_ghost_frontend.h"
#include "ghosts_frontends/purple_ghost_frontend.h"
#include "ghosts_frontends/red_ghost_frontend.h"
#include "screen_text_display.h"

#include <QWidget>
#include <QPainter>

class GameArena : public QWidget
{
public:
    explicit GameArena(QWidget* parent, const Model& model);

private:
    void paintEvent([[maybe_unused]] QPaintEvent* event) override;

    void drawArena(QPainter& painter) const;
    void drawCharacters(QPainter& painter) const;
    void drawBalls(QPainter& painter) const;

    void drawPacman(QPainter& painter) const;
    void drawGhosts(QPainter& painter) const;
    void drawGhost(QPainter& painter, const AbstractGhostFrontend& ghostFrontend) const;
    void drawFoodballs(QPainter& painter) const;
    void drawPowerballs(QPainter& painter) const;
    void drawFoodball(QPainter& painter, const Foodball& foodball) const;
    void drawPowerball(QPainter& painter, const Powerball& powerball) const;

    void drawScreenTextDisplay(QPainter& painter);

    const Model& model_;
    std::unique_ptr<QPixmap> arenaPixmap;
    std::unique_ptr<PacmanFrontend> pacmanFrontend_;
    std::unique_ptr<BlueGhostFrontend> blueGhostFrontend_;
    std::unique_ptr<OrangeGhostFrontend> orangeGhostFrontend_;
    std::unique_ptr<PurpleGhostFrontend> purpleGhostFrontend_;
    std::unique_ptr<RedGhostFrontend> redGhostFrontend_;
    std::unique_ptr<ScreenTextDisplay> screenTextDisplay_;
};
