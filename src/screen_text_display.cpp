#include "screen_text_display.h"

ScreenTextDisplay::ScreenTextDisplay()
{
    gameResult_ = GameResult::noResultYet;
    score_ = 0;
}

QRectF ScreenTextDisplay::boundingRect() const
{
    return QRect(x_, y_, width_, height_);
}

void ScreenTextDisplay::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    QPen penRed(Qt::red);
    QPen penYellow(Qt::yellow);
    QPen penBlue(Qt::blue);
    painter->setPen(penRed);
    QFont font = painter->font();
    font.setPointSize (pointSize_);
    painter->setFont(font);

    if(gameResult_ == GameResult::gameWin)
    {
        painter->setPen(penYellow);
        painter->drawText(boundingRect(),Qt::AlignTop | Qt::AlignHCenter,"CONGRATULATIONS");
        painter->drawText(boundingRect(),Qt::AlignCenter, "FINAL SCORE : " + QString::number(score_));
        painter->setPen(penBlue);
        painter->drawText(boundingRect(),Qt::AlignBottom | Qt::AlignHCenter,"PRESS SPACE TO RESTART");
    }
    else if(gameResult_ == GameResult::gameLost)
    {
        painter->setPen(penRed);
        painter->drawText(boundingRect(),Qt::AlignTop | Qt::AlignHCenter,"GAME OVER");
        painter->setPen(penYellow);
        painter->drawText(boundingRect(),Qt::AlignCenter, "FINAL SCORE : " + QString::number(score_));
        painter->setPen(penBlue);
        painter->drawText(boundingRect(),Qt::AlignBottom | Qt::AlignHCenter,"PRESS SPACE TO RESTART");
    }
    else if(gameResult_ == GameResult::noResultYet)
    {
        painter->drawText(boundingRect(),Qt::AlignCenter, "PRESS SPACE TO START");
    }
}
