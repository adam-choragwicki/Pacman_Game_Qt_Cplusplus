#pragma once

#include <QtWidgets/QGraphicsItem>
#include <QtGui/QPen>

class CustomGraphicsItem : public QGraphicsItem
{
public:
    explicit CustomGraphicsItem(const QRectF& rect);

    [[nodiscard]] QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override = 0;

    bool operator<(const CustomGraphicsItem& other) const;

protected:
    bool drawRect_{};

    const QRectF rect_;
    QPen rectPen_;

    const uint id_;
};
