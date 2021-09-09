#include "drawer.h"
#include "log_manager.h"

QGraphicsScene* Drawer::scene_ = nullptr;
QGraphicsPixmapItem* Drawer::mapItem_ = nullptr;

void Drawer::drawGameArena()
{
    mapItem_ = scene_->addPixmap(QPixmap(":/images/map.png"));
}

void Drawer::setGameArenaVisibility(bool isVisible)
{
    if(isVisible)
    {
        mapItem_->setVisible(true);
    }
    else
    {
        mapItem_->setVisible(false);
    }
}

void Drawer::updateScene()
{
    scene_->update(scene_->sceneRect());
}

void Drawer::drawItem(QGraphicsItem* item)
{
    scene_->addItem(item);
}
