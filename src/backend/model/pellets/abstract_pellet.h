#pragma once

class Coordinates;

#include "custom_graphics_item.h"

class AbstractPellet : public CustomGraphicsItem
{
public:
    explicit AbstractPellet(const Coordinates& coordinates, int diameter, int offsetX, int offsetY);
    ~AbstractPellet() override = 0;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    bool operator<(const AbstractPellet& other) const;
};
