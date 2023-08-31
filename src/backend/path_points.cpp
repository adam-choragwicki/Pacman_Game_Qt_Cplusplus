#include "path_points.h"

PathPoints::PathPoints() : PATH_POINTS(generatePathPoints()), POWERBALL_POSITIONS(generatePowerballPositions()), FOODBALL_POSITIONS(generateFoodballPositions())
{}

bool PathPoints::isPathPointValid(const Coordinates& coordinates) const
{
    /*Check if given point is accessible for movable characters*/
    return PATH_POINTS.contains(coordinates);
}

std::set<Coordinates> PathPoints::generatePathPoints()
{
    std::set<Coordinates> pathPoints;

    /*HORIZONTAL LINES*/
    /*LINE 1*/
    pathPoints.merge(generatePathPointsBetweenPoints(35, 35, 274, 35));
    pathPoints.merge(generatePathPointsBetweenPoints(340, 35, 579, 35));

    /*LINE 2*/
    pathPoints.merge(generatePathPointsBetweenPoints(35, 121, 579, 121));

    /*LINE 3*/
    pathPoints.merge(generatePathPointsBetweenPoints(35, 187, 144, 187));
    pathPoints.merge(generatePathPointsBetweenPoints(209, 187, 274, 187));
    pathPoints.merge(generatePathPointsBetweenPoints(340, 187, 406, 187));
    pathPoints.merge(generatePathPointsBetweenPoints(470, 187, 579, 187));

    /*LINE 4*/
    pathPoints.merge(generatePathPointsBetweenPoints(209, 252, 406, 252));

    /*LINE 5 - MIDDLE LINE*/
    pathPoints.merge(generatePathPointsBetweenPoints(0, 318, 209, 318));
    pathPoints.merge(generatePathPointsBetweenPoints(406, 318, 614, 318));

    /*LINE 6*/
    pathPoints.merge(generatePathPointsBetweenPoints(209, 384, 406, 384));

    /*LINE 7*/
    pathPoints.merge(generatePathPointsBetweenPoints(35, 449, 274, 449));
    pathPoints.merge(generatePathPointsBetweenPoints(340, 449, 579, 449));

    /*LINE 8*/
    pathPoints.merge(generatePathPointsBetweenPoints(35, 514, 79, 514));
    pathPoints.merge(generatePathPointsBetweenPoints(144, 514, 470, 514));
    pathPoints.merge(generatePathPointsBetweenPoints(536, 514, 579, 514));

    /*LINE 9*/
    pathPoints.merge(generatePathPointsBetweenPoints(35, 580, 144, 580));
    pathPoints.merge(generatePathPointsBetweenPoints(209, 580, 274, 580));
    pathPoints.merge(generatePathPointsBetweenPoints(340, 580, 406, 580));
    pathPoints.merge(generatePathPointsBetweenPoints(470, 580, 579, 580));

    /*LINE 10*/
    pathPoints.merge(generatePathPointsBetweenPoints(35, 645, 579, 645));

    /*VERTICAL LINES*/
    /*LINE 1*/
    pathPoints.merge(generatePathPointsBetweenPoints(35, 35, 35, 187));
    pathPoints.merge(generatePathPointsBetweenPoints(35, 449, 35, 514));
    pathPoints.merge(generatePathPointsBetweenPoints(35, 580, 35, 645));

    /*LINE 2*/
    pathPoints.merge(generatePathPointsBetweenPoints(79, 514, 79, 580));

    /*LINE 3*/
    pathPoints.merge(generatePathPointsBetweenPoints(144, 35, 144, 580));

    /*LINE 4*/
    pathPoints.merge(generatePathPointsBetweenPoints(209, 121, 209, 187));
    pathPoints.merge(generatePathPointsBetweenPoints(209, 252, 209, 449));
    pathPoints.merge(generatePathPointsBetweenPoints(209, 514, 209, 580));

    /*LINE 5*/
    pathPoints.merge(generatePathPointsBetweenPoints(274, 35, 274, 121));
    pathPoints.merge(generatePathPointsBetweenPoints(274, 187, 274, 252));
    pathPoints.merge(generatePathPointsBetweenPoints(274, 449, 274, 514));
    pathPoints.merge(generatePathPointsBetweenPoints(274, 580, 274, 645));

    /*LINE 6*/
    pathPoints.merge(generatePathPointsBetweenPoints(340, 35, 340, 121));
    pathPoints.merge(generatePathPointsBetweenPoints(340, 187, 340, 252));
    pathPoints.merge(generatePathPointsBetweenPoints(340, 449, 340, 514));
    pathPoints.merge(generatePathPointsBetweenPoints(340, 580, 340, 645));

    /*LINE 7*/
    pathPoints.merge(generatePathPointsBetweenPoints(406, 121, 406, 187));
    pathPoints.merge(generatePathPointsBetweenPoints(406, 252, 406, 449));
    pathPoints.merge(generatePathPointsBetweenPoints(406, 514, 406, 580));

    /*LINE 8*/
    pathPoints.merge(generatePathPointsBetweenPoints(470, 35, 470, 580));

    /*LINE 9*/
    pathPoints.merge(generatePathPointsBetweenPoints(536, 514, 536, 580));

    /*LINE 10*/
    pathPoints.merge(generatePathPointsBetweenPoints(579, 35, 579, 187));
    pathPoints.merge(generatePathPointsBetweenPoints(579, 449, 579, 514));
    pathPoints.merge(generatePathPointsBetweenPoints(579, 580, 579, 645));

    return pathPoints;
}

std::set<Coordinates> PathPoints::generatePathPointsBetweenPoints(int startX, int startY, int endX, int endY)
{
    std::set<Coordinates> pathPoints;

    /*Vertical line*/
    if(startX == endX)
    {
        /*Vertical line from startY to endY*/
        if(startY < endY)
        {
            for(int y = startY; y <= endY; y++)
            {
                pathPoints.insert({startX, y});
            }
        }
    }

    /*Horizontal line*/
    if(startY == endY)
    {
        /*Horizontal line from startX to endX*/
        if(startX < endX)
        {
            for(int x = startX; x <= endX; x++)
            {
                pathPoints.insert({x, startY});
            }
        }
    }

    return pathPoints;
}

std::set<Coordinates> PathPoints::generateFoodballPositions()
{
    /*Coordinates (X,Y) where foodballs will be placed*/
    const std::array<int, 10> verticalLinesXCoordinates = {35, 79, 144, 209, 274, 340, 406, 470, 536, 579};
    const std::array<int, 10> horizontalLinesYCoordinates = {35, 121, 187, 252, 318, 384, 449, 514, 580, 645};

    std::set<Coordinates> foodballPositions;

    for(int x : verticalLinesXCoordinates)
    {
        for(int y : horizontalLinesYCoordinates)
        {
            const Coordinates foodballCoordinates(x, y);

            /*Check if point is on available path*/
            if(PATH_POINTS.contains(foodballCoordinates))
            {
                /*Skip points where powerballs are*/
                if(POWERBALL_POSITIONS.contains(foodballCoordinates))
                {
                    continue;
                }

                foodballPositions.insert(foodballCoordinates);
            }
        }
    }

    if(foodballPositions.size() != TARGET_FOODBALLS_COUNT)
    {
        throw std::runtime_error("Error, wrong number of foodball positions generated");
    }

    return foodballPositions;
}

std::set<Coordinates> PathPoints::generatePowerballPositions()
{
    std::set<Coordinates> powerballPositions{Coordinates{35, 75}, Coordinates{579, 75}, Coordinates{35, 514}, Coordinates{579, 514}};

    if(powerballPositions.size() != TARGET_POWERBALLS_COUNT)
    {
        throw std::runtime_error("Error, wrong number of powerball positions generated");
    }

    return powerballPositions;
}
