#include "model/pacman.h"
#include "pixmap_providers/pacman_pixmap_provider.h"
#include <QtGui/QPainter>

Pacman::Pacman(PacmanPixmapProvider* pacmanPixmapProvider) : MovableCharacter(STARTING_COORDINATES, INITIAL_DIRECTION, ANIMATION_SPEED_FACTOR, ANIMATION_PHASES_COUNT), pacmanPixmapProvider_(pacmanPixmapProvider)
{
    direction_ = Direction::LEFT;
}

void Pacman::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    CustomGraphicsItem::paint(painter, option, widget);

    QPixmap pixmap = pacmanPixmapProvider_->getPixmap(direction_, animationPhase_);

    drawPixmapAvoidingArtifacts(painter, &pixmap);
}
