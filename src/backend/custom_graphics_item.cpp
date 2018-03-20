#include "custom_graphics_item.h"
#include "id_generator.h"
#include <QtGui/QPainter>

CustomGraphicsItem::CustomGraphicsItem(const QRectF& rect) : rect_(rect), id_(IdGenerator::generateId())
{
    rectPen_ = QPen(Qt::red, 1);

    globalDrawBoundingRect_ = false;
}

QRectF CustomGraphicsItem::boundingRect() const
{
    return rect_;
}

void CustomGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    if(globalDrawBoundingRect_ || drawBoundingRect_)
    {
        painter->setPen(rectPen_);
        double penWidth = rectPen_.widthF();

        /* This is required to avoid artifacts */
        const int multiplier = 2;
        const QRectF adjustedRect = rect_.adjusted(multiplier * penWidth, multiplier * penWidth, -multiplier * penWidth, -multiplier * penWidth);
        painter->drawRect(adjustedRect);
    }
}

bool CustomGraphicsItem::operator<(const CustomGraphicsItem& other) const
{
    return id_ < other.id_;
}

void CustomGraphicsItem::drawPixmapAvoidingArtifacts(QPainter* painter, const QPixmap* pixmap)
{
    const double penWidth = painter->pen().widthF();
    const QRectF targetRect = rect_.adjusted(penWidth / 2, penWidth / 2, -penWidth / 2, -penWidth / 2);
    painter->drawPixmap(targetRect.toRect(), *pixmap);
}
