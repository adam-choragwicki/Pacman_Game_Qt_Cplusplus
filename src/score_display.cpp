#include "score_display.h"
#include <QPainter>

ScoreDisplay::ScoreDisplay()
{
    score_ = 0;
}

QRectF ScoreDisplay::boundingRect() const
{
    return QRect(x_, y_, width_, height_);
}

void ScoreDisplay::paint(QPainter *painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    QFont font = painter->font();
    font.setPointSize(pointSize_);

    painter->setPen(QPen(Qt::white));
    painter->setFont(font);

    painter->drawText(boundingRect(),Qt::AlignTop | Qt::AlignHCenter, "Score: " + QString::number(score_));
}
