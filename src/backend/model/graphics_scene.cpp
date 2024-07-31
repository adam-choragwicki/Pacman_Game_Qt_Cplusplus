#include "graphics_scene.h"
#include "config.h"

GraphicsScene::GraphicsScene() :
        QGraphicsScene(0, 0, Config::instance().worldMap.WORLD_HORIZONTAL_SQUARES_COUNT * Config::instance().worldMap.PRIMARY_SQUARE_SIZE, Config::instance().worldMap.WORLD_VERTICAL_SQUARES_COUNT * Config::instance().worldMap.PRIMARY_SQUARE_SIZE)
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
