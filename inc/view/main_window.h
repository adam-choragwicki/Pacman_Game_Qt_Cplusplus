#pragma once

#include "model.h"
#include "view/ball_frontend.h"
#include "view/score_display.h"
#include "view/game_arena.h"

#include <QDialog>
#include <QKeyEvent>
#include <QPaintEvent>
#include <memory>

class MainWindow : public QDialog
{
Q_OBJECT

signals:
    void keyPressedEvent(Key key);

public:
    explicit MainWindow(Model* model);
    ~MainWindow() override = default;

    void paintEvent([[maybe_unused]] QPaintEvent* event) override;
    void drawScoreDisplay(QPainter& painter);

private:
    void keyPressEvent(QKeyEvent* event) override;

    Model* model_;
    std::unique_ptr<GameArena> gameArena_;
    std::unique_ptr<ScoreDisplay> scoreDisplay_;
};
