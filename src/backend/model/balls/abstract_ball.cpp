#include "abstract_ball.h"
#include "config.h"
#include <QtGui/QBrush>

AbstractBall::AbstractBall(const Coordinates& coordinates) : coordinates_(coordinates)
{
    rect_.setSize(QSize(Config::Foodball::DIAMETER, Config::Foodball::DIAMETER));
    rect_.translate(coordinates.x_, coordinates.y_);

    setBrush(Qt::white);

    setRect(rect_);
}

AbstractBall::~AbstractBall() = default;

bool AbstractBall::operator<(const AbstractBall& other) const
{
    if(rect_.x() < other.rect_.x())
    {
        return true;
    }
    else if(rect_.x() > other.rect_.x())
    {
        return false;
    }
    else
    {
        if(rect_.y() < other.rect_.y())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
