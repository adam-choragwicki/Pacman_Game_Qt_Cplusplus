#include "arena.h"
#include "model/walls/horizontal_wall.h"

Arena::Arena() : horizontalSquaresCount_(50), verticalSquaresCount_(50)
{
    for(int horizontalSquareIndex = 0; horizontalSquareIndex < horizontalSquaresCount_; ++horizontalSquareIndex)
    {
        for(int verticalSquareIndex = 0; verticalSquareIndex < verticalSquaresCount_; ++verticalSquareIndex)
        {
            Coordinates coordinates(horizontalSquareIndex, verticalSquareIndex);

            const auto&[iter, inserted] = walls_.try_emplace(coordinates, nullptr);

            if(!inserted)
            {
                throw std::runtime_error("Error, trying to add duplicate coordinates to map");
            }
        }
    }

    addSingleWall(1, 1);
    addSingleWall(2, 2);
    addSingleWall(3, 3);
    addSingleWall(4, 4);
    addSingleWall(5, 5);

    qDebug() << "Initialized " << walls_.size() << " empty walls";
}

void Arena::addSingleWall(int x, int y, const QColor& color)
{
    Coordinates coordinates(x, y);

    if(walls_.contains(coordinates))
    {
        if(walls_.at(coordinates) == nullptr)
        {
            walls_.at(coordinates) = new HorizontalWall(x, y, color);
        }
        else
        {
            throw std::runtime_error("Error, trying to add wall to non-empty coordinates");
        }
    }
    else
    {
        throw std::runtime_error("Error, trying to dereference non-existing coordinates");
    }
}

int Arena::invertYForDrawing(int y)
{
    return verticalSquaresCount_ - y;
}
