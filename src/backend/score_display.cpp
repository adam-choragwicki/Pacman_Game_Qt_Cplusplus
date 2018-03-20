#include "score_display.h"
#include "score_manager.h"
#include <QtGui/QPainter>

ScoreDisplay::ScoreDisplay(const ScoreManager& scoreManager) : scoreManager_(scoreManager)
{
    initializePainterData();
}

void ScoreDisplay::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsTextItem::paint(painter, option, widget);

    QRect scoreDisplayBoundingRect(X, Y, WIDTH, HEIGHT);

    painter->setPen(painterPen_);
    painter->setFont(painterFont_);

    painter->drawText(scoreDisplayBoundingRect, Qt::AlignTop | Qt::AlignHCenter, "Score: " + QString::number(scoreManager_.getScore()));
}

void ScoreDisplay::initializePainterData()
{
    painterPen_ = QPen(Qt::white);

    QFont font;
    font.setPointSize(ScoreDisplay::FONT_POINT_SIZE);

    painterFont_ = font;
}
