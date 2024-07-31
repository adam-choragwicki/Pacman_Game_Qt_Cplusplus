#include "model/pacman.h"
#include <QtGui/QPainter>

#include "abstract_pixmap_provider.h"

Pacman::Pacman(AbstractPixmapProvider* pixmapProvider) : MovableCharacter(STARTING_COORDINATES, INITIAL_DIRECTION, ANIMATION_SPEED_FACTOR, ANIMATION_PHASES_COUNT), pixmapProvider_(pixmapProvider)
{
    direction_ = Direction::LEFT;
}

void Pacman::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    CustomGraphicsItem::paint(painter, option, widget);

    painter->setRenderHint(QPainter::Antialiasing);

    QPixmap pixmap = pixmapProvider_->getPixmap(direction_, animationPhase_);

    if(pixmap.isNull())
    {
        qDebug() << "NULL PIXMAP";
    }

    drawPixmapAvoidingArtifacts(painter, &pixmap);
}
