#pragma once

#include "model/tiles/abstract_tile.h"

class CornerWallSW : public AbstractTile
{
public:
    CornerWallSW(int x, int y, const QColor& color);
};
