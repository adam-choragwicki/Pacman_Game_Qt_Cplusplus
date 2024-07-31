#include "custom_graphics_item.h"
#include "id_generator.h"
#include <QtGui/QPainter>

CustomGraphicsItem::CustomGraphicsItem(const QRectF& rect) : rect_(rect), id_(IdGenerator::generateId())
{
    rectPen_ = QPen(Qt::red, 1);
}

QRectF CustomGraphicsItem::boundingRect() const
{
    return rect_;
}

void CustomGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    //    painter->setRenderHint(QPainter::Antialiasing);

    //    if(drawRect_)
    //    {
    //        painter->setPen(rectPen_);
    //        double penWidth = rectPen_.widthF();
    //
    //        /* This is required to avoid artifacts */
    //        const int multiplier = 2;
    //        const QRectF adjustedRect = rect_.adjusted(multiplier * penWidth, multiplier * penWidth, -multiplier * penWidth, -multiplier * penWidth);
    //        painter->drawRect(adjustedRect);
    //    }
}

bool CustomGraphicsItem::operator<(const CustomGraphicsItem& other) const
{
    return id_ < other.id_;
}
