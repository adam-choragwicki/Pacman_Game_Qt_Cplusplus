#include "game_map.h"

GameMap::GameMap()
{
    if(!allGenerated)
    {
        generateAllPaths();
        generateFoodballPositions();
        generatePowerballPositions();

        allGenerated = true;
    }
}

GameMap::~GameMap()
{

}

bool GameMap::isPathPointValid(const QPoint& point) const
{
    /*Check if given point is accessible for movable characters*/
    return pathPoints_.contains(point);
}

void GameMap::generateAllPaths()
{
    /*HORIZONTAL LINES*/
    /*LINE 1*/
    generatePathPointsBetweenPoints(35, 35, 274, 35);
    generatePathPointsBetweenPoints(340, 35, 579, 35);

    /*LINE 2*/
    generatePathPointsBetweenPoints(35, 121, 579, 121);

    /*LINE 3*/
    generatePathPointsBetweenPoints(35, 187, 144, 187);
    generatePathPointsBetweenPoints(209, 187, 274, 187);
    generatePathPointsBetweenPoints(340, 187, 406, 187);
    generatePathPointsBetweenPoints(470, 187, 579, 187);

    /*LINE 4*/
    generatePathPointsBetweenPoints(209, 252, 406, 252);

    /*LINE 5 - MIDDLE LINE*/
    generatePathPointsBetweenPoints(0, 318, 209, 318);
    generatePathPointsBetweenPoints(406, 318, 614, 318);

    /*LINE 6*/
    generatePathPointsBetweenPoints(209, 384,406, 384);

    /*LINE 7*/
    generatePathPointsBetweenPoints(35, 449, 274, 449);
    generatePathPointsBetweenPoints(340, 449, 579, 449);

    /*LINE 8*/
    generatePathPointsBetweenPoints(35, 514, 79, 514);
    generatePathPointsBetweenPoints(144, 514, 470, 514);
    generatePathPointsBetweenPoints(536, 514, 579, 514);

    /*LINE 9*/
    generatePathPointsBetweenPoints(35, 580, 144, 580);
    generatePathPointsBetweenPoints(209, 580, 274, 580);
    generatePathPointsBetweenPoints(340, 580, 406, 580);
    generatePathPointsBetweenPoints(470, 580, 579, 580);

    /*LINE 10*/
    generatePathPointsBetweenPoints(35, 645, 579, 645);

    /*VERTICAL LINES*/
    /*LINE 1*/
    generatePathPointsBetweenPoints(35, 35, 35, 187);
    generatePathPointsBetweenPoints(35, 449, 35, 514);
    generatePathPointsBetweenPoints(35, 580, 35, 645);

    /*LINE 2*/
    generatePathPointsBetweenPoints(79, 514, 79, 580);

    /*LINE 3*/
    generatePathPointsBetweenPoints(144, 35, 144, 580);

    /*LINE 4*/
    generatePathPointsBetweenPoints(209, 121, 209, 187);
    generatePathPointsBetweenPoints(209, 252, 209, 449);
    generatePathPointsBetweenPoints(209, 514, 209, 580);

    /*LINE 5*/
    generatePathPointsBetweenPoints(274, 35, 274, 121);
    generatePathPointsBetweenPoints(274, 187, 274, 252);
    generatePathPointsBetweenPoints(274, 449, 274, 514);
    generatePathPointsBetweenPoints(274, 580, 274, 645);

    /*LINE 6*/
    generatePathPointsBetweenPoints(340, 35, 340, 121);
    generatePathPointsBetweenPoints(340, 187, 340, 252);
    generatePathPointsBetweenPoints(340, 449, 340, 514);
    generatePathPointsBetweenPoints(340, 580, 340, 645);

    /*LINE 7*/
    generatePathPointsBetweenPoints(406, 121, 406, 187);
    generatePathPointsBetweenPoints(406, 252, 406, 449);
    generatePathPointsBetweenPoints(406, 514, 406, 580);

    /*LINE 8*/
    generatePathPointsBetweenPoints(470, 35, 470, 580);

    /*LINE 9*/
    generatePathPointsBetweenPoints(536, 514, 536, 580);

    /*LINE 10*/
    generatePathPointsBetweenPoints(579, 35, 579, 187);
    generatePathPointsBetweenPoints(579, 449, 579, 514);
    generatePathPointsBetweenPoints(579, 580, 579, 645);
}

void GameMap::generatePathPointsBetweenPoints(int startX, int startY, int endX, int endY)
{
    /*Vertical line*/
    if (startX == endX)
    {
        /*Vertical line from startY to endY*/
        if (startY < endY)
        {
            for(int y = startY; y <= endY; y++)
            {
                pathPoints_.insert({startX, y});
            }
        }
    }

    /*Horizontal line*/
    if (startY == endY)
    {
        /*Horizontal line from startX to endX*/
        if (startX < endX)
        {
            for(int x = startX; x <= endX; x++)
            {
                pathPoints_.insert({x, startY});
            }
        }
    }
}

void GameMap::generateFoodballPositions() const
{
    /*Coordinates (x_,y_) where foodballs will be placed*/
    const QVector<int> verticalLinesXCoordinates={35, 79, 144, 209, 274, 340, 406, 470, 536, 579};
    const QVector<int> horizontalLinesYCoordinates={35, 121, 187, 252, 318, 384, 449, 514, 580, 645};

    for(int x : verticalLinesXCoordinates)
    {
        for(int y : horizontalLinesYCoordinates)
        {
            const QPoint foodballPoint(x, y);

            /*Check if point is on path*/
            if(pathPoints_.contains(foodballPoint))
            {
                /*Skip points where powerballs are*/
                if((foodballPoint == QPoint{35, 75}) || (foodballPoint == QPoint{579, 75}) || (foodballPoint == QPoint{35, 514}) || (foodballPoint == QPoint{579, 514}))
                {
                    continue;
                }

                foodballPositions_.insert({x, y});
            }
        }
    }

    if(foodballPositions_.size() != targetFoodballCount_)
    {
        throw std::runtime_error("Wrong number of foodball positions generated");
    }
}

void GameMap::generatePowerballPositions() const
{
    const QSet<QPoint> powerballPositions {{35, 75}, {579, 75}, {35, 514}, {579, 514}};

    for(const QPoint& powerballPosition : powerballPositions)
    {
        powerballPositions_.insert(powerballPosition);
    }

    if(powerballPositions_.size() != targetPowerballCount_)
    {
        throw std::runtime_error("Wrong number of powerball positions generated");
    }
}
