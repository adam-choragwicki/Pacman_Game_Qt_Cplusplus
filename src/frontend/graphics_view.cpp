#include "graphics_view.h"
#include "model/graphics_scene.h"
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>

GraphicsView::GraphicsView(GraphicsScene* scene, const WhatToDrawManager& whatToDrawManager, QWidget* parent) : QGraphicsView(scene, parent), whatToDrawManager_(whatToDrawManager)
{
    setFocusPolicy(Qt::NoFocus);
    setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    arenaPixmap_ = std::make_unique<QPixmap>(":/map/map.png");

    //    setRenderHint(QPainter::Antialiasing, true);

    connect(&fpsTimer_, &QTimer::timeout, this, &GraphicsView::updateFPS);
    fpsTimer_.start(500); // Update FPS every 500ms
    frameTimeTimer_.start();

    initializePainterData();

    viewport()->installEventFilter(this);
}

void GraphicsView::drawBackground(QPainter* painter, const QRectF& rect)
{
    QGraphicsView::drawBackground(painter, rect);

    if(whatToDrawManager_.drawBackground_)
    {
        painter->drawPixmap(0, 0, 614, 740, *arenaPixmap_);
    }
}

void GraphicsView::drawForeground(QPainter* painter, const QRectF& rect)
{
    /* Ensure FPS counter is drawn on top of scene and always visible */
    QGraphicsView::drawForeground(painter, rect);

    if(whatToDrawManager_.drawFPSCounter_)
    {
        ++frameCount_;

        painter->setPen(fpsCounterPen_);
        painter->setFont(fpsCounterFont_);

        const QPointF topLeft = mapToScene(viewport()->rect().topLeft());
        painter->drawText(topLeft + QPointF(10, 20), QString("FPS: %1").arg(qRound(currentFPS_)));
    }
}

void GraphicsView::updateFPS()
{
    qint64 elapsed = frameTimeTimer_.elapsed();
    currentFPS_ = (frameCount_ * 1000.0) / elapsed;
    frameCount_ = 0;
    frameTimeTimer_.restart();
}

bool GraphicsView::eventFilter(QObject* obj, QEvent* event)
{
    if(event->type() == QEvent::Wheel)
    {
        /* Ignore mouse wheel events to disable scene scrolling */
        return true;
    }

    return QGraphicsView::eventFilter(obj, event);
}

void GraphicsView::initializePainterData()
{
    fpsCounterFont_.setFamily("Arial");
    fpsCounterFont_.setPointSize(20);
    fpsCounterFont_.setBold(true);

    fpsCounterPen_.setColor(Qt::red);
}

void GraphicsView::updateViewport(const QList<QRectF>& dirtyRegions)
{
    for(const QRectF& rect : dirtyRegions)
    {
        viewport()->update(rect.toRect());
    }
}
