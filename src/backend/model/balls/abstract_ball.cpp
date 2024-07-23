#include "abstract_ball.h"
#include "config.h"
#include <QtGui/QPainter>

AbstractBall::AbstractBall(const Coordinates& coordinates, int diameter) : CustomGraphicsItem(QRectF(0, 0, diameter, diameter))
{
    setPos(coordinates.x_, coordinates.y_);
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
}
