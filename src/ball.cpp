#include "ball.h"
#include "drawer.h"

#include <QPainter>

Ball::Ball(const Coordinates& coordinates, int diameter) : coordinates_(coordinates), diameter_(diameter)
{
    Drawer::drawItem(this);
}

Ball::~Ball()
{
    Drawer::eraseItem(this);
}

QRectF Ball::boundingRect() const
{
    return QRect(coordinates_.x_, coordinates_.y_, diameter_, diameter_);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(Qt::white));
    painter->drawEllipse(coordinates_.x_, coordinates_.y_, diameter_, diameter_);
}

Foodball::Foodball(const Coordinates& coordinates) : Ball(coordinates, diameter_)
{}

Powerball::Powerball(const Coordinates& coordinates) : Ball(coordinates, diameter_)
{}
