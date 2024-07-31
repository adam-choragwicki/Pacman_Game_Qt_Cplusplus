#pragma once

#include "model/tiles/abstract_tile.h"

class HorizontalWall : public AbstractTile
{
public:
    HorizontalWall(int x, int y, const QColor& color);
};
