#pragma once

#include "common.h"
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class ScreenTextDisplay : public QGraphicsItem
{
public:
    ScreenTextDisplay();
    void setScore(int score) {score_ = score;}
    void setGameResult(GameResult gameResult) {gameResult_ = gameResult;}

private:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    const int width_ = 600;
    const int height_ = 200;
    const int x_ = 614 / 2 - width_ / 2;
    const int y_ = 714 / 2 - height_ / 2;
    const int pointSize_ = 30;

    GameResult gameResult_;
    int score_;
};
