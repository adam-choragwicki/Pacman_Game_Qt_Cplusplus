#pragma once

#include "model/tiles/abstract_tile.h"

class VerticalWall : public AbstractTile
{
public:
    VerticalWall(int x, int y, const QColor& color);
};
