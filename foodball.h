#pragma once

#include <QVector>
#include <QPoint>
#include <QGraphicsItem>

class Foodball : public QGraphicsItem
{
public:
    Foodball(int x, int y);

private:    
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;

    const int diameter_ = 7;

    int x_;
    int y_;
};
