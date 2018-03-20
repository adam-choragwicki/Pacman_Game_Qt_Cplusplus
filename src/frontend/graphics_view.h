#pragma once

#include <QGraphicsView>
#include <QTimer>
#include <QElapsedTimer>
#include "model/what_to_draw_manager.h"

class QTimer;
class GraphicsScene;

class GraphicsView : public QGraphicsView
{
Q_OBJECT

public:
    explicit GraphicsView(GraphicsScene* scene, const WhatToDrawManager& whatToDrawManager, QWidget* parent = nullptr);

    void drawBackground(QPainter* painter, const QRectF& rect) override;
    void drawForeground(QPainter* painter, const QRectF& rect) override;
    bool eventFilter(QObject* obj, QEvent* event) override;

    void updateViewport(const QList<QRectF>& dirtyRegions);

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

    const WhatToDrawManager& whatToDrawManager_;
};
