#pragma once

#include "model/walls/abstract_wall.h"
#include "coordinates.h"

class Arena
{
public:
    Arena();

    [[nodiscard]] const std::map<Coordinates, AbstractWall*>& getWalls() const
    { return walls_; }

private:
    std::map<Coordinates, AbstractWall*> walls_;

    void addSingleWall(int x, int y, const QColor& color = Qt::black);


    int invertYForDrawing(int y);

    const int horizontalSquaresCount_;
    const int verticalSquaresCount_;
};
