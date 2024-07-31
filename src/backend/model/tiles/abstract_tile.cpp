#include "model/tiles/abstract_tile.h"
#include "config.h"

AbstractTile::AbstractTile(int x, int y, const QColor& color) : CustomGraphicsItem(QRect(x * Config::instance().worldMap.PRIMARY_SQUARE_SIZE, y * Config::instance().worldMap.PRIMARY_SQUARE_SIZE, Config::instance().worldMap.PRIMARY_SQUARE_SIZE, Config::instance().worldMap.PRIMARY_SQUARE_SIZE)), coordinates_(x, y), color_(color)
{
    setAcceptHoverEvents(true);
}

void AbstractTile::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    CustomGraphicsItem::paint(painter, option, widget);
    painter->drawPixmap(rect_.toRect(), *pixmap_);
}
