#pragma once

class ScoreManager;

#include <QtWidgets/QGraphicsTextItem>
#include <QtGui/QPen>
#include <QtGui/QFont>

class ScoreDisplay : public QGraphicsTextItem
{
public:
    explicit ScoreDisplay(const ScoreManager& scoreManager);
    ~ScoreDisplay() override = default;

    static const int X = 0;
    static const int Y = 680;
    static const int WIDTH = 600;
    static const int HEIGHT = 200;
    static const int FONT_POINT_SIZE = 30;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    void initializePainterData();

    const ScoreManager& scoreManager_;

    QFont painterFont_;
    QPen painterPen_;
};
