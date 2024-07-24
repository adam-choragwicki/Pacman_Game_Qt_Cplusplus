#pragma once

#include "movable_character.h"
#include "images_urls.h"

class Pacman : public MovableCharacter
{
public:
    Pacman();
    void advanceAnimation() override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    void initializePixmaps();

    QPixmap left1Pixmap_, left2Pixmap_, left3Pixmap_, left4Pixmap_;
    QPixmap up1Pixmap_, up2Pixmap_, up3Pixmap_, up4Pixmap_;
    QPixmap down1Pixmap_, down2Pixmap_, down3Pixmap_, down4Pixmap_;
    QPixmap right1Pixmap_, right2Pixmap_, right3Pixmap_, right4Pixmap_;
};
