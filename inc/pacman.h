#pragma once

#include "movable_character_interface.h"

#include <QGraphicsItem>
#include <QTimer>

class Pacman : public QGraphicsItem, public MovableCharacterInterface
{
public:
    explicit Pacman(const GameMap& gameMap);
    ~Pacman() override;

    QTimer& getMovementTimer() {return movementTimer_;}

    void reset() override;
    void startMovement() override;
    void stopMovement() override;

    void move();

private:
    [[nodiscard]] QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void advanceAnimation()  override;
    void loadImages();

    inline static const Coordinates startingCoordinates_{320, 514};

    QTimer movementTimer_;

    QPixmap left1Pixmap_, left2Pixmap_, left3Pixmap_, left4Pixmap_;
    QPixmap up1Pixmap_, up2Pixmap_, up3Pixmap_, up4Pixmap_;
    QPixmap down1Pixmap_, down2Pixmap_, down3Pixmap_, down4Pixmap_;
    QPixmap right1Pixmap_, right2Pixmap_, right3Pixmap_, right4Pixmap_;

    const int animationSpeedFactor_ = 6;
};
