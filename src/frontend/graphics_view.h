#pragma once

#include <QGraphicsView>
#include <QTimer>
#include <QElapsedTimer>

class QTimer;

class GraphicsView : public QGraphicsView
{
Q_OBJECT

signals:
    void mousePositionChangedEvent(const QPointF& mousePosition);
    void mouseLeftButtonClicked(const QPointF& mousePosition);

public:
    explicit GraphicsView(QGraphicsScene* scene, const bool& drawBackground, QWidget* parent = nullptr);

    void drawBackground(QPainter* painter, const QRectF& rect) override;
    void drawForeground(QPainter* painter, const QRectF& rect) override;
    bool eventFilter(QObject* obj, QEvent* event) override;

    void updateViewport();

private slots:
    void updateFPS();

private:
    void initializePainterData();

    QTimer fpsTimer_;
    QElapsedTimer frameTimeTimer_;
    int frameCount_{};
    double currentFPS_{};

    QFont fpsCounterFont_;
    QPen fpsCounterPen_;

    std::unique_ptr<QPixmap> arenaPixmap_;

    const bool& drawBackground_;
};
