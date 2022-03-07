#pragma once

#include <QVector>
#include <QPoint>
#include <QGraphicsItem>

class Powerball : public QGraphicsItem
{
public:
    Powerball(int x, int y);

private:
    [[nodiscard]] QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;

    const int diameter_ = 15;

    int x_;
    int y_;
};
