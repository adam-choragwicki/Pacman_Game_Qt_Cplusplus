#include "foodball.h"

Foodball::Foodball(const Coordinates& coordinates) : AbstractBall(coordinates)
{
    rect_.setSize(QSize(DIAMETER, DIAMETER));
    rect_.translate(OFFSET_X, OFFSET_Y);
    setRect(rect_);
}
