#include "arena.h"
#include "model/tiles/straight_walls/horizontal_wall.h"
#include "model/tiles/straight_walls/vertical_wall.h"
#include "model/tiles/rounded_walls/rounded_horizontal_wall.h"
#include "model/tiles/rounded_walls/rounded_vertical_wall.h"
#include "model/tiles/path.h"
#include "tiles/corner_walls/corner_wall_nw.h"
#include "tiles/corner_walls/corner_wall_sw.h"
#include "tiles/corner_walls/corner_wall_ne.h"
#include "tiles/corner_walls/corner_wall_se.h"
#include "config.h"

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

    const Config& config = Config::instance();

    //left vertical wall
    for(int row = 1; row <= config.worldMap.WORLD_VERTICAL_SQUARES_COUNT; ++row)
    {
        addVerticalWall(0, row);
    }

    //right vertical wall
    for(int row = 1; row <= config.worldMap.WORLD_VERTICAL_SQUARES_COUNT; ++row)
    {
        addVerticalWall(config.worldMap.WORLD_HORIZONTAL_SQUARES_COUNT - 1, row);
    }

    //top horizontal wall
    for(int column = 1; column < config.worldMap.WORLD_HORIZONTAL_SQUARES_COUNT - 1; ++column)
    {
        addHorizontalWall(column, 0);
    }

    //bottom horizontal wall
    for(int column = 1; column < config.worldMap.WORLD_HORIZONTAL_SQUARES_COUNT - 1; ++column)
    {
        addHorizontalWall(column, config.worldMap.WORLD_VERTICAL_SQUARES_COUNT + 1);
    }

    addCornerWallNW(0, 0);
    addCornerWallNE(config.worldMap.WORLD_VERTICAL_SQUARES_COUNT - 1, 0);
    addCornerWallSW(0, config.worldMap.WORLD_HORIZONTAL_SQUARES_COUNT + 1);
    addCornerWallSE(config.worldMap.WORLD_VERTICAL_SQUARES_COUNT - 1, config.worldMap.WORLD_HORIZONTAL_SQUARES_COUNT + 1);



    //    for(int row = 0; row < config.worldMap.WORLD_HORIZONTAL_SQUARES_COUNT; ++row)
    //    {
    //        for(int column = 0; column < config.worldMap.WORLD_VERTICAL_SQUARES_COUNT; ++column)
    //        {
    //            addVerticalWall(column, row);
    //        }
    //    }

    //    addPath(0, 10);
    //    addPath(1, 10);
    //    addPath(2, 10);
    //    addPath(3, 10);
    //    addPath(4, 10);
    //    addPath(5, 10);
    //
    //    addVerticalWall(7, 10);
    //
    //    //    addRoundedVerticalWall(1, 1);
    //    addVerticalWall(13, 10);
    //
    //    addPath(15, 10);
    //    addPath(16, 10);
    //    addPath(17, 10);
    //    addPath(18, 10);
    //    addPath(19, 10);

    //    addRoundedVerticalWall(1, 1);
    //    addVerticalWall(1, 2);
    //    addVerticalWall(1, 3);
    //    addVerticalWall(1, 4);
    //    addRoundedVerticalWall(1, 6);
    //
    //    addHorizontalWall(4, 6);
    //    addHorizontalWall(5, 6);
    //    addHorizontalWall(6, 6);
    //    addRoundedHorizontalWall(8, 6);
    //    addRoundedHorizontalWall(10, 6);

    qDebug() << "Initialized " << walls_.size() << " empty walls";
}

//int Arena::invertYForDrawing(int y)
//{
//    return verticalSquaresCount_ - y;
//}

void Arena::addVerticalWall(int x, int y, const QColor& color)
{
    Coordinates coordinates(x, y);

    if(walls_.contains(coordinates))
    {
        if(walls_.at(coordinates) == nullptr)
        {
            walls_.at(coordinates) = new VerticalWall(x, y, color);
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

void Arena::addHorizontalWall(int x, int y, const QColor& color)
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

void Arena::addRoundedHorizontalWall(int x, int y, const QColor& color)
{
    Coordinates coordinates(x, y);

    if(walls_.contains(coordinates))
    {
        if(walls_.at(coordinates) == nullptr)
        {
            walls_.at(coordinates) = new RoundedHorizontalWall(x, y, color);
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

void Arena::addRoundedVerticalWall(int x, int y, const QColor& color)
{
    Coordinates coordinates(x, y);

    if(walls_.contains(coordinates))
    {
        if(walls_.at(coordinates) == nullptr)
        {
            walls_.at(coordinates) = new RoundedVerticalWall(x, y, color);
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

void Arena::addPath(int x, int y, const QColor& color)
{
    Coordinates coordinates(x, y);

    if(walls_.contains(coordinates))
    {
        if(walls_.at(coordinates) == nullptr)
        {
            walls_.at(coordinates) = new Path(x, y, color);
        }
        else
        {
            throw std::runtime_error("Error, trying to add path to non-empty coordinates");
        }
    }
    else
    {
        throw std::runtime_error("Error, trying to dereference non-existing coordinates");
    }
}

void Arena::addCornerWallNW(int x, int y, const QColor& color)
{
    Coordinates coordinates(x, y);

    if(walls_.contains(coordinates))
    {
        if(walls_.at(coordinates) == nullptr)
        {
            walls_.at(coordinates) = new CornerWallNW(x, y, color);
        }
        else
        {
            throw std::runtime_error("Error, trying to add path to non-empty coordinates");
        }
    }
    else
    {
        throw std::runtime_error("Error, trying to dereference non-existing coordinates");
    }
}

void Arena::addCornerWallSW(int x, int y, const QColor& color)
{
    Coordinates coordinates(x, y);

    if(walls_.contains(coordinates))
    {
        if(walls_.at(coordinates) == nullptr)
        {
            walls_.at(coordinates) = new CornerWallSW(x, y, color);
        }
        else
        {
            throw std::runtime_error("Error, trying to add path to non-empty coordinates");
        }
    }
    else
    {
        throw std::runtime_error("Error, trying to dereference non-existing coordinates");
    }
}

void Arena::addCornerWallNE(int x, int y, const QColor& color)
{
    Coordinates coordinates(x, y);

    if(walls_.contains(coordinates))
    {
        if(walls_.at(coordinates) == nullptr)
        {
            walls_.at(coordinates) = new CornerWallNE(x, y, color);
        }
        else
        {
            throw std::runtime_error("Error, trying to add path to non-empty coordinates");
        }
    }
    else
    {
        throw std::runtime_error("Error, trying to dereference non-existing coordinates");
    }
}

void Arena::addCornerWallSE(int x, int y, const QColor& color)
{
    Coordinates coordinates(x, y);

    if(walls_.contains(coordinates))
    {
        if(walls_.at(coordinates) == nullptr)
        {
            walls_.at(coordinates) = new CornerWallSE(x, y, color);
        }
        else
        {
            throw std::runtime_error("Error, trying to add path to non-empty coordinates");
        }
    }
    else
    {
        throw std::runtime_error("Error, trying to dereference non-existing coordinates");
    }
}
