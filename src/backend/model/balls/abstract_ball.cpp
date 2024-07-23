#include "abstract_ball.h"
#include "config.h"
#include <QtGui/QPainter>

AbstractBall::AbstractBall(const Coordinates& coordinates, int diameter) : coordinates_(coordinates), diameter_(diameter)
{
    id_ = ++currentIdCounter;

    setPos(coordinates.x_, coordinates.y_);
    //    rect_.translate(coordinates.x_, coordinates.y_);
}

AbstractBall::~AbstractBall() = default;

void AbstractBall::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setBrush(Qt::white);
    painter->drawEllipse(boundingRect());
}

bool AbstractBall::operator<(const AbstractBall& other) const
{
    return id_ < other.id_;

//    if(rect_.x() < other.rect_.x())
//    {
//        return true;
//    }
//    else if(rect_.x() > other.rect_.x())
//    {
//        return false;
//    }
//    else
//    {
//        if(rect_.y() < other.rect_.y())
//        {
//            return true;
//        }
//        else
//        {
//            return false;
//        }
//    }
}
