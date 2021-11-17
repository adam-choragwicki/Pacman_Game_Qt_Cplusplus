#pragma once

#include "movable_character_interface.h"

#include <QGraphicsItem>
#include <QTimer>

class Pacman : public QGraphicsItem, public MovableCharacterInterface
{
public:
    Pacman();

    QTimer& getMovementTimer() {return movementTimer_;}

    void advanceAnimation()  override;
    void reset() override;
    void startMovement() override;
    void stopMovement() override;
    void resumeMovement() override;

    void move();

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void loadImages();

    static const int startingX_ = 320;
    static const int startingY_ = 514;

    QTimer movementTimer_;

    QPixmap left1Pixmap_, left2Pixmap_, left3Pixmap_, left4Pixmap_;
    QPixmap up1Pixmap_, up2Pixmap_, up3Pixmap_, up4Pixmap_;
    QPixmap down1Pixmap_, down2Pixmap_, down3Pixmap_, down4Pixmap_;
    QPixmap right1Pixmap_, right2Pixmap_, right3Pixmap_, right4Pixmap_;

    const int animationSpeedFactor_ = 6;
};
