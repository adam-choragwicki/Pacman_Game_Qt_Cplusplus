#pragma once

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class Drawer
{
public:
    Drawer() = delete;

    static void setScene(QGraphicsScene* scene) {scene_ = scene;}
    static void drawGameArena();
    static void setGameArenaVisibility(bool isVisible);
    static void updateScene();
    static void drawItem(QGraphicsItem* item);
    static void eraseItem(QGraphicsItem* item);

private:
    inline static QGraphicsScene* scene_ {};
    inline static QGraphicsPixmapItem* mapItem_ {};
};
