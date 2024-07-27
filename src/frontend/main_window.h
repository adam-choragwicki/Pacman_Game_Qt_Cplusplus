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

    void updateViewport(const QList<QRectF>& dirtyRegions);

    [[nodiscard]] QTimer* getViewportUpdateTimer() const
    { return viewportUpdateTimer_; }

private:
    void keyPressEvent(QKeyEvent* event) override;

    void centerOnScreen(QScreen* screen);
    void centerOnPrimaryScreen();

    const Model& model_;

    GraphicsView* graphicsView_{};

    QTimer* viewportUpdateTimer_;

    static constexpr auto VIEWPORT_UPDATE_INTERVAL = std::chrono::milliseconds(17);
};
