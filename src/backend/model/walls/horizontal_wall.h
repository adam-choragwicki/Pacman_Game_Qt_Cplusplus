#pragma once

#include "abstract_wall.h"

class HorizontalWall : public AbstractWall
{
public:
    HorizontalWall(int x, int y, const QColor& color);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};
