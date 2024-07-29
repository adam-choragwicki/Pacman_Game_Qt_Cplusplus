#include "horizontal_wall.h"
#include <QtGui/QPainter>

HorizontalWall::HorizontalWall(int x, int y, const QColor& color) :
//        AbstractTile(x, y, QRect(x * Config::instance().worldMap.PRIMARY_SQUARE_SIZE, y * Config::instance().worldMap.PRIMARY_SQUARE_SIZE, Config::instance().wall.WIDTH, Config::instance().wall.HEIGHT)), color_(color)
        AbstractWall(x, y, QRect(x * 50, y * 50, 50, 50), color)
{

}

void HorizontalWall::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    //    painter->setPen(pen_);
    //    painter->setBrush(color_);

    QPen pen(Qt::green, 30);

    painter->setPen(pen);
    painter->setBrush(Qt::green);


    painter->drawRect(rect_);

    //        Utilities::drawCoordinates(painter, sceneBoundingRect());
}
