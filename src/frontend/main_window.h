#pragma once

#include "game_arena.h"
#include <QMainWindow>

class Model;
class GraphicsView;

class MainWindow : public QMainWindow
{
Q_OBJECT

signals:
    void keyPressedEvent(QKeyEvent* event);

public:
    explicit MainWindow(const Model& model);
    ~MainWindow() override = default;

    void paintEvent([[maybe_unused]] QPaintEvent* event) override;
    void drawScoreDisplay(QPainter& painter);

    [[nodiscard]] QTimer& getFrontendUpdateTimer()
    { return frontendUpdateTimer_; }

private:
    void keyPressEvent(QKeyEvent* event) override;
    void centerOnScreen();

    QTimer frontendUpdateTimer_;

    const Model& model_;
    GameArena gameArena_;

    GraphicsView* graphicsView_{};
};
