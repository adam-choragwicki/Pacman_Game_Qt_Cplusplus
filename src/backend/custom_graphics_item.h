#pragma once

#include <QtWidgets/QGraphicsItem>
#include <QtGui/QPen>

class CustomGraphicsItem : public QGraphicsItem
{
public:
    explicit CustomGraphicsItem(const QRectF& rect);

    [[nodiscard]] QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override = 0;

    // every derived type has to define its custom QGraphicsItem type
//    [[nodiscard]] int type() const override = 0;

    [[nodiscard]] uint getId() const
    { return id_; }

protected:
    bool drawRect_{};

    QRectF rect_;
    QPen pen_;
    QPen rectPen_;

private:
    const uint id_;
};
