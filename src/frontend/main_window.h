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

    void updateViewport();

private:
    void keyPressEvent(QKeyEvent* event) override;

    void centerOnScreen(QScreen* screen);
    void centerOnPrimaryScreen();

    const Model& model_;
//    GameArena gameArena_;

    GraphicsView* graphicsView_{};
};
