#include "graphics_scene.h"

GraphicsScene::GraphicsScene() : QGraphicsScene(0, 0, ARENA_WIDTH_PX, ARENA_HEIGHT_PX)
{
    connect(this, &GraphicsScene::changed, this, &GraphicsScene::updateDirtyRegion);
}

void GraphicsScene::updateDirtyRegion(const QList<QRectF>& dirtyRegion)
{
    for(const QRectF& rect : dirtyRegion)
    {
        dirtyRegions_.append(rect);
    }
}
