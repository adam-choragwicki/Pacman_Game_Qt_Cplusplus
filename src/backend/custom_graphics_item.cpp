#include "custom_graphics_item.h"
#include "id_generator.h"
#include <QtGui/QPainter>

CustomGraphicsItem::CustomGraphicsItem(const QRectF& rect) : rect_(rect), id_(IdGenerator::generateId())
{
    pen_ = Qt::NoPen;
    rectPen_ = QPen(Qt::red, 1);
}

QRectF CustomGraphicsItem::boundingRect() const
{
    return rect_;
}

void CustomGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if(drawRect_)
    {
        painter->setPen(rectPen_);
        painter->drawRect(rect_);
    }
}
