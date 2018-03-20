#pragma once

#include "graphics_view.h"
#include <QMainWindow>

class Model;

class MainWindow : public QMainWindow
{
Q_OBJECT

signals:
    void keyPressedEvent(QKeyEvent* event);

public:
    explicit MainWindow(const Model& model);
    ~MainWindow() override = default;

    void updateViewport(const QList<QRectF>& dirtyRegions);

    [[nodiscard]] QTimer* getViewportUpdateTimer() const
    { return viewportUpdateTimer_.get(); }

private:
    void keyPressEvent(QKeyEvent* event) override;

    void centerOnScreen(QScreen* screen);
    void centerOnPrimaryScreen();

    const Model& model_;

    std::unique_ptr<GraphicsView> graphicsView_;

    std::unique_ptr<QTimer> viewportUpdateTimer_;

    static constexpr auto VIEWPORT_UPDATE_INTERVAL = std::chrono::milliseconds(17);
};
