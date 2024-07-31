#pragma once

#include "model/tiles/abstract_tile.h"

class RoundedHorizontalWall : public AbstractTile
{
public:
    RoundedHorizontalWall(int x, int y, const QColor& color);
};
