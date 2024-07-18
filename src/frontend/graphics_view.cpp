#include "graphics_view.h"
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>

GraphicsView::GraphicsView(QGraphicsScene* scene, QWidget* parent) : QGraphicsView(scene, parent)
{
    arenaPixmap_ = std::make_unique<QPixmap>(":/images/map.png");

    setRenderHint(QPainter::Antialiasing, true);
    setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(&fpsTimer_, &QTimer::timeout, this, &GraphicsView::updateFPS);
    fpsTimer_.start(1000); // Update FPS every second
    frameTimeTimer_.start();

    initializePainterData();

    viewport()->installEventFilter(this);
}

void GraphicsView::drawBackground(QPainter* painter, const QRectF& rect)
{
    QGraphicsView::drawBackground(painter, rect);
    painter->drawPixmap(0, 0, 614, 740, *arenaPixmap_);
}

void GraphicsView::drawForeground(QPainter* painter, const QRectF& rect)
{
    /* Ensure FPS counter is drawn on top of scene and always visible */
    QGraphicsView::drawForeground(painter, rect);
    ++frameCount_;

    painter->setPen(fpsCounterPen_);
    painter->setFont(fpsCounterFont_);

    // Get the viewport's top-left coordinates
    const QPointF topLeft = mapToScene(viewport()->rect().topLeft());
    painter->drawText(topLeft + QPointF(10, 20), QString("FPS: %1").arg(currentFPS_));
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
    if(event->type() == QEvent::MouseMove)
    {
        auto* mouseEvent = dynamic_cast<QMouseEvent*>(event);
        QPointF mousePositionOnScene = mapToScene(mouseEvent->pos());
        emit mousePositionChangedEvent(mousePositionOnScene);
    }
    else if(event->type() == QEvent::MouseButtonPress)
    {
        auto* mouseEvent = dynamic_cast<QMouseEvent*>(event);
        QPointF mousePositionOnScene = mapToScene(mouseEvent->pos());

        if(mouseEvent->button() == Qt::MouseButton::LeftButton)
        {
            emit mouseLeftButtonClicked(mousePositionOnScene);
        }
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

void GraphicsView::updateViewport()
{
    viewport()->update();
}
