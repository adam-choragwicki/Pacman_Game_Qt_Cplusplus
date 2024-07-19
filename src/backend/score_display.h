#pragma once

#include "score_manager.h"
#include <QtWidgets/QGraphicsTextItem>

class ScoreDisplay : public QGraphicsTextItem
{
public:
    ScoreDisplay(int x, int y);
    ~ScoreDisplay() override = default;

    static const int X = 0;
    static const int Y = 680;
    static const int WIDTH = 600;
    static const int HEIGHT = 200;
    static const int FONT_POINT_SIZE = 30;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};
