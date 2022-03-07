#include "powerball.h"
#include <QPoint>
#include <QPainter>
#include <QDebug>

Powerball::Powerball(int x, int y)
{
    x_ = x;
    y_ = y;
}

QRectF Powerball::boundingRect() const
{
    return QRect(x_, y_, diameter_, diameter_);
}

void Powerball::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(Qt::white));

    painter->drawEllipse(x_, y_, diameter_, diameter_);
}
