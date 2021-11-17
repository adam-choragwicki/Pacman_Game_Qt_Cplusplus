#pragma once

#include <QGraphicsItem>

class ScoreDisplay : public QGraphicsItem
{
public:
    ScoreDisplay();

    int getScore() {return score_;}

    void setScore(int score);

    void rewardPlayerForEatingFoodball() {score_ += 1;}
    void rewardPlayerForEatingGhost() {score_ += 200;}
    void rewardPlayerForEatingPowerball() {score_ += 100;}
    void resetScore(){score_ = 0;}

private:    
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    const int x_ = 0;
    const int y_ = 680;
    const int width_ = 600;
    const int height_ = 200;
    const int pointSize_ = 30;

    int score_;
};
