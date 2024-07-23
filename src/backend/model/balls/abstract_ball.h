#pragma once

#include "coordinates.h"
#include <QRect>
#include <QtWidgets/QGraphicsItem>

class AbstractBall : public QGraphicsItem
{
public:
    explicit AbstractBall(const Coordinates& coordinates, int diameter);
    ~AbstractBall() override = 0;

    [[nodiscard]] QRectF boundingRect() const override
    {
        return QRectF(0, 0, diameter_, diameter_);
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    //    QRectF boundingRect() const override;

    //    [[nodiscard]] const Coordinates& getCoordinates() const
    //    { return coordinates_; }

    [[nodiscard]] QRect getRect() const
    { return rect_; }

    bool operator<(const AbstractBall& other) const;

protected:
    QRect rect_;

    const int diameter_;

private:
    const Coordinates coordinates_;

    inline static int currentIdCounter = 0;

    int id_;
};
