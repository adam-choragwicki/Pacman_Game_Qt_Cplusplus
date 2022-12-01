#pragma once

#include "model.h"

#include "view/pacman_frontend.h"
#include "view/blue_ghost_frontend.h"
#include "view/orange_ghost_frontend.h"
#include "view/purple_ghost_frontend.h"
#include "view/red_ghost_frontend.h"
#include "view/ball_frontend.h"
#include "view/screen_text_display.h"

#include <QWidget>
#include <QPainter>

class GameArena : public QWidget
{
public:
    explicit GameArena(QWidget* parent, Model* model);

private:
    void paintEvent([[maybe_unused]] QPaintEvent* event) override;

    void drawArena(QPainter& painter) const;
    void drawCharacters(QPainter& painter) const;
    void drawBalls(QPainter& painter) const;

    void drawPacman(QPainter& painter) const;
    void drawGhosts(QPainter& painter) const;
    void drawGhost(QPainter& painter, AbstractGhostFrontend* ghostFrontend) const;
    void drawFoodballs(QPainter& painter) const;
    void drawPowerballs(QPainter& painter) const;
    void drawFoodBall(QPainter& painter, const FoodballFrontend& foodballFrontend) const;
    void drawPowerball(QPainter& painter, const PowerballFrontend& powerballFrontend) const;

    void drawScreenTextDisplay(QPainter& painter);

    Model* model_;
    std::unique_ptr<QPixmap> arenaPixmap;
    std::unique_ptr<PacmanFrontend> pacmanFrontend_;
    std::unique_ptr<BlueGhostFrontend> blueGhostFrontend_;
    std::unique_ptr<OrangeGhostFrontend> orangeGhostFrontend_;
    std::unique_ptr<PurpleGhostFrontend> purpleGhostFrontend_;
    std::unique_ptr<RedGhostFrontend> redGhostFrontend_;
    std::unique_ptr<ScreenTextDisplay> screenTextDisplay_{};

    std::vector<FoodballFrontend> foodballsFrontend_;
    std::vector<PowerballFrontend> powerballsFrontend_;
};
