#include "abstract_ball.h"
#include "config.h"
#include <QtGui/QPainter>

AbstractBall::AbstractBall(const Coordinates& coordinates, int diameter, int offsetX, int offsetY) : CustomGraphicsItem(QRectF(offsetX, offsetY, diameter, diameter))
{
    setPos(coordinates.x_, coordinates.y_);
    drawRect_ = true;
}

AbstractBall::~AbstractBall() = default;

void AbstractBall::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    CustomGraphicsItem::paint(painter, option, widget);

    painter->setBrush(Qt::white);
    painter->drawEllipse(boundingRect());
}

bool AbstractBall::operator<(const AbstractBall& other) const
{
    return id_ < other.id_;
}
