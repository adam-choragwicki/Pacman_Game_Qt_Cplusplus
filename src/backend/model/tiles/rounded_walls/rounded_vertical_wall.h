#pragma once

#include "model/tiles/abstract_tile.h"

class RoundedVerticalWall : public AbstractTile
{
public:
    RoundedVerticalWall(int x, int y, const QColor& color);
};
