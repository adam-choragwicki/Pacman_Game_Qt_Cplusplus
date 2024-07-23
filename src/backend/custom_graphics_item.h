#pragma once

#include <QtWidgets/QGraphicsItem>
#include <QtGui/QPen>

class CustomGraphicsItem : public QGraphicsItem
{
public:
    explicit CustomGraphicsItem(const QRectF& rect);

    [[nodiscard]] QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override = 0;

protected:
    bool drawRect_{};

    QRectF rect_;
    QPen pen_;
    QPen rectPen_;

    const uint id_;
};
