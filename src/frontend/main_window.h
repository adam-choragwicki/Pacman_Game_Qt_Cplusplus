#pragma once

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

    GraphicsView* graphicsView_{};
};
