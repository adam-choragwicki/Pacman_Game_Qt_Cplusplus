#include "abstract_pellet.h"
#include "coordinates.h"
#include <QtGui/QPainter>

AbstractPellet::AbstractPellet(const Coordinates& coordinates, int diameter, int offsetX, int offsetY) : CustomGraphicsItem(QRectF(offsetX, offsetY, diameter, diameter))
{
    setPos(coordinates.x_, coordinates.y_);
    drawRect_ = true;
}

AbstractPellet::~AbstractPellet() = default;

void AbstractPellet::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    CustomGraphicsItem::paint(painter, option, widget);

    painter->setBrush(Qt::white);
    painter->drawEllipse(rect_);
}
