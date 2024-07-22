#pragma once

#include "movable_character.h"
#include "moving_object.h"
#include "images_urls.h"

class Pacman : public MovableCharacter
{
public:
    Pacman();
    void advanceAnimation() override;

    [[nodiscard]] QRectF boundingRect() const override
    { return {0, 0, 30, 30}; }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    QPixmap left1Pixmap_, left2Pixmap_, left3Pixmap_, left4Pixmap_;
    QPixmap up1Pixmap_, up2Pixmap_, up3Pixmap_, up4Pixmap_;
    QPixmap down1Pixmap_, down2Pixmap_, down3Pixmap_, down4Pixmap_;
    QPixmap right1Pixmap_, right2Pixmap_, right3Pixmap_, right4Pixmap_;

    void loadImages(const std::array<std::string, 16>& imagesUrls);
};
