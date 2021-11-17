#pragma once

#include <QVector>
#include <QPixmap>

class GameMap
{
public:
    GameMap();
    static bool isPathPointValid(QPoint const& point);
    static QVector<QPoint> const& getPathPoints() {return pathPoints_;}
    QVector<QPoint> generateFoodballPositions() const;
    QVector<QPoint> generatePowerballPositions() const;

private:
    void generatePathPoints(int startX, int startY, int endX, int endY);

    const int targetFoodballCount_ = 88;
    const int targetPowerballCount_ = 4;

    static QVector<QPoint> pathPoints_;
};
