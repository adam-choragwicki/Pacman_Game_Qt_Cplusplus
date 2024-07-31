#pragma once

#include "model/tiles/abstract_tile.h"

class CornerWallNW : public AbstractTile
{
public:
    CornerWallNW(int x, int y, const QColor& color);
};
