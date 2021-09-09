#include "foodball.h"
#include "game_map.h"
#include <QPainter>

Foodball::Foodball(int x, int y)
{
    x_ = x;
    y_ = y;
}

QRectF Foodball::boundingRect() const
{
    return QRect(x_, y_, diameter_, diameter_);
}

void Foodball::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(Qt::white));

    painter->drawEllipse(x_, y_, diameter_, diameter_);
}
