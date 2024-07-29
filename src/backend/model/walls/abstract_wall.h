#pragma once

#include "custom_graphics_item.h"
#include "coordinates.h"

class AbstractWall : public CustomGraphicsItem
{
public:
    AbstractWall(int x, int y, const QRectF& rect, const QColor& color) : CustomGraphicsItem(rect), coordinates_(x, y), color_(color)
    {
        setAcceptHoverEvents(true);
    }

private:
    const QColor color_;
    const Coordinates coordinates_;
};
