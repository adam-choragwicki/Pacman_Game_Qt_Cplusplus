#pragma once

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class Drawer
{
public:
    Drawer() = delete;
    Drawer(const Drawer&) = delete;
    Drawer& operator=(Drawer&) = delete;
    Drawer(const Drawer&&) = delete;
    Drawer& operator=(Drawer&&) = delete;

    static void setScene(QGraphicsScene* scene) {scene_ = scene;}
    static void drawGameArena();
    static void setGameArenaVisibility(bool isVisible);
    static void updateScene();
    static void drawItem(QGraphicsItem* item);

private:
    static QGraphicsScene* scene_;
    static QGraphicsPixmapItem* mapItem_;
};
