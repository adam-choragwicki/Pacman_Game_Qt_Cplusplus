#pragma once

#include <QtWidgets/QGraphicsScene>

class GraphicsScene : public QGraphicsScene
{
public:
    GraphicsScene();

    [[nodiscard]] QList<QRectF>& getDirtyRegions()
    { return dirtyRegions_; }

private slots:
    void updateDirtyRegion(const QList<QRectF>& dirtyRegion);

private:
    static const int ARENA_WIDTH_PX = 614;
    static const int ARENA_HEIGHT_PX = 730;

    QList<QRectF> dirtyRegions_;
};
