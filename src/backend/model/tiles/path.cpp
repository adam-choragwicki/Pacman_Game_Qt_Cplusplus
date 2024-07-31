#include "path.h"

Path::Path(int x, int y, const QColor& color) : AbstractTile(x, y, color)
{}

void Path::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    //    AbstractTile::paint(painter, option, widget);

    //    QPen pen;
    painter->setBrush(Qt::green);

    painter->drawRect(rect_);
}
