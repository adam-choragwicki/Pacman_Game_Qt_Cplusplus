#pragma once

#include <utility>
#include <iostream>

struct Coordinates
{
    friend std::ostream& operator<<(std::ostream& os, const Coordinates& coordinates);

    Coordinates(int x, int y);
    Coordinates operator+(const std::pair<int, int>& coordinates) const;
    Coordinates& operator+=(const Coordinates& coordinates);

    int x_;
    int y_;
};

bool operator==(const Coordinates& coordinates1, const Coordinates& coordinates2);
bool operator!=(const Coordinates& coordinates1, const Coordinates& coordinates2);
bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2);
