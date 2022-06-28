#include "drawer.h"

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
    scene_->update();
}

void Drawer::drawItem(QGraphicsItem* item)
{
    scene_->addItem(item);
}

void Drawer::eraseItem(QGraphicsItem* item)
{
    scene_->removeItem(item);
}
