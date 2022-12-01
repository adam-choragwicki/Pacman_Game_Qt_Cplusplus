#include "coordinates.h"

bool operator==(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    return (coordinates1.x_ == coordinates2.x_) && (coordinates1.y_ == coordinates2.y_);
}

bool operator!=(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    return !(coordinates1 == coordinates2);
}

bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    if(coordinates1.x_ < coordinates2.x_)
    {
        return true;
    }
    else if(coordinates1.x_ > coordinates2.x_)
    {
        return false;
    }
    else
    {
        return coordinates1.y_ < coordinates2.y_;
    }
}

Coordinates::Coordinates(int x, int y) : x_(x), y_(y)
{

}

Coordinates Coordinates::operator+(const std::pair<int, int>& coordinates) const
{
    return {x_ + coordinates.first, y_ + coordinates.second};
}

Coordinates& Coordinates::operator+=(const Coordinates& coordinates)
{
    x_ += coordinates.x_;
    y_ += coordinates.y_;

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Coordinates& coordinates)
{
    os << "[" << coordinates.x_ << "," << coordinates.y_ << "]";
    return os;
}
