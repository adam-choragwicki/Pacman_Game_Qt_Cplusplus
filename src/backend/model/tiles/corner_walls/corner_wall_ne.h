#pragma once

#include "model/tiles/abstract_tile.h"

class CornerWallNE : public AbstractTile
{
public:
    CornerWallNE(int x, int y, const QColor& color);
};
