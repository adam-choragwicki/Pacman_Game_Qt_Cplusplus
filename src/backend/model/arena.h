#pragma once

#include "model/tiles/abstract_tile.h"
#include "coordinates.h"

class Arena
{
public:
    Arena();

    [[nodiscard]] const std::map<Coordinates, AbstractTile*>& getTiles() const
    { return walls_; }

private:
    std::map<Coordinates, AbstractTile*> walls_;

    void addCornerWallNW(int x, int y, const QColor& color = Qt::black);
    void addCornerWallSW(int x, int y, const QColor& color = Qt::black);
    void addCornerWallNE(int x, int y, const QColor& color = Qt::black);
    void addCornerWallSE(int x, int y, const QColor& color = Qt::black);

    void addVerticalWall(int x, int y, const QColor& color = Qt::black);
    void addHorizontalWall(int x, int y, const QColor& color = Qt::black);

    void addRoundedVerticalWall(int x, int y, const QColor& color = Qt::black);
    void addRoundedHorizontalWall(int x, int y, const QColor& color = Qt::black);

    void addPath(int x, int y, const QColor& color = Qt::black);

//    int invertYForDrawing(int y);

    const int horizontalSquaresCount_;
    const int verticalSquaresCount_;
};
