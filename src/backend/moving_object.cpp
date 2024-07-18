#include "moving_object.h"

MovingObject::MovingObject(const QRectF& rect) : CustomGraphicsItem(rect)
{}

void MovingObject::move()
{
//    moveBy(movementVector_.getHorizontalSpeed(), movementVector_.getVerticalSpeed());
}

//Direction MovingObject::getHorizontalDirection() const
//{
//    return movementVector_.getHorizontalDirection();
//}
