#pragma once

#include "custom_graphics_item.h"
#include "coordinates.h"
#include <QtGui/QPainter>

class AbstractTile : public CustomGraphicsItem
{
public:
    AbstractTile(int x, int y, const QColor& color);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

protected:
    QPixmap* pixmap_{};

private:
    const QColor color_;
    const Coordinates coordinates_;
};
