#pragma once

class Coordinates;

#include "custom_graphics_item.h"

class AbstractBall : public CustomGraphicsItem
{
public:
    explicit AbstractBall(const Coordinates& coordinates, int diameter);
    ~AbstractBall() override = 0;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    bool operator<(const AbstractBall& other) const;
};
