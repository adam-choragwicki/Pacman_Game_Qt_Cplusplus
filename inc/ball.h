#pragma once

#include "coordinates.h"

#include <QGraphicsItem>

class Ball : public QGraphicsItem
{
protected:
    Ball(const Coordinates& coordinates, int diameter);
    ~Ball() override;

    [[nodiscard]] QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;

private:
    const Coordinates coordinates_;
    const int diameter_;
};

class Foodball : public Ball
{
public:
    explicit Foodball(const Coordinates& coordinates);
    ~Foodball() override = default;

private:
    static const int diameter_ = 7;
};

class Powerball : public Ball
{
public:
    explicit Powerball(const Coordinates& coordinates);
    ~Powerball() override = default;

private:
    static const int diameter_ = 15;
};
