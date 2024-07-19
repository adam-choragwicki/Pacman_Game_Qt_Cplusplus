#include "score_display.h"
#include <QtGui/QPainter>

ScoreDisplay::ScoreDisplay(int x, int y)
{}

void ScoreDisplay::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsTextItem::paint(painter, option, widget);

    QRect scoreDisplayBoundingRect(X, Y, WIDTH, HEIGHT);


    QFont font = painter->font();
    font.setPointSize(ScoreDisplay::FONT_POINT_SIZE);

    painter->setPen(QPen(Qt::white));
    painter->setFont(font);

//    painter->drawText(scoreDisplayBoundingRect, Qt::AlignTop | Qt::AlignHCenter, "Score: " + QString::number(model_.getScoreManager().getScore()));

    painter->drawText(scoreDisplayBoundingRect, Qt::AlignTop | Qt::AlignHCenter, "Score: " + QString::number(0));
}
