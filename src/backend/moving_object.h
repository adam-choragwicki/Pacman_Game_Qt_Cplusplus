#pragma once

#include "custom_graphics_item.h"
#include "common.h"

class MovingObject : public CustomGraphicsItem
{
public:
    explicit MovingObject(const QRectF& rect);

//    [[nodiscard]] Direction getHorizontalDirection() const;

    virtual void move();

    void setNextDirection(Direction direction)
    { nextDirection_ = direction; }

    virtual void advanceAnimation() = 0;

protected:
    bool fancyGraphics_{};

    int animationState_{};

    Direction direction_;
    Direction nextDirection_;
};
