#pragma once

#include "model/tiles/abstract_tile.h"

class Path : public AbstractTile
{
public:
    Path(int x, int y, const QColor& color);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};
