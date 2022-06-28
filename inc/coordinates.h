#pragma once

#include <utility>
#include <QPoint>

struct Coordinates
{
    Coordinates(int x, int y);
    Coordinates(const QPoint& coordinates);
    Coordinates operator+(const std::pair<int, int>& coordinates) const;
    Coordinates& operator+=(const Coordinates& coordinates);

    operator QPoint()
    {
        return {x_, y_};
    }

    int x_;
    int y_;
};

bool operator==(const Coordinates& coordinates1, const Coordinates& coordinates2);
bool operator!=(const Coordinates& coordinates1, const Coordinates& coordinates2);
bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2);
