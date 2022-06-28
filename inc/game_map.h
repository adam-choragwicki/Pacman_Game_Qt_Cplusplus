#pragma once

#include "coordinates.h"

#include <QSet>
#include <QPoint>

class GameMap
{
public:
    GameMap();
    ~GameMap();

    [[nodiscard]] bool isPathPointValid(const QPoint& point) const;
    [[nodiscard]] const QSet<QPoint>& getFoodballPositions() const {return foodballPositions_;};
    [[nodiscard]] const QSet<QPoint>& getPowerballPositions() const {return powerballPositions_;};

private:
    static const int targetFoodballCount_ = 88;
    static const int targetPowerballCount_ = 4;

    inline static QSet<QPoint> pathPoints_;
    inline static QSet<QPoint> foodballPositions_;
    inline static QSet<QPoint> powerballPositions_;
    inline static bool allGenerated = false;

    void generatePathPointsBetweenPoints(int startX, int startY, int endX, int endY);
    void generateAllPaths();
    void generateFoodballPositions() const;
    void generatePowerballPositions() const;
};
