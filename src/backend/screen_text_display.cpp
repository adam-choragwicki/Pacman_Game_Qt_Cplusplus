#include <QtGui/QPainter>
#include "screen_text_display.h"
#include "score_manager.h"
#include "model/game_state_manager.h"

ScreenTextDisplay::ScreenTextDisplay(const ScoreManager& scoreManager) : scoreManager_(scoreManager)
{}

void ScreenTextDisplay::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsTextItem::paint(painter, option, widget);

    QRect screenTextDisplayBoundingRect(X, Y, WIDTH, HEIGHT);

    QPen penRed(Qt::red);
    QPen penYellow(Qt::yellow);
    QPen penBlue(Qt::blue);
    painter->setPen(penRed);

    QFont font = painter->font();
    font.setPointSize(ScreenTextDisplay::FONT_POINT_SIZE);
    painter->setFont(font);

    bool isReadyToStart = gameStateManager_->isReadyToStart();
    bool isPaused = gameStateManager_->isPaused();
    bool isRunning = gameStateManager_->isRunning();
    bool isStopped = gameStateManager_->isStopped();

    if(isReadyToStart)
    {
        painter->drawText(screenTextDisplayBoundingRect, Qt::AlignCenter, "PRESS SPACE TO START");
    }
    else if(isPaused)
    {
        painter->setPen(penYellow);
        font.setPointSize(ScreenTextDisplay::FONT_POINT_SIZE + 20);
        painter->drawText(screenTextDisplayBoundingRect, Qt::AlignVCenter | Qt::AlignHCenter, "PAUSED");
    }
    else if(isRunning)
    {
        //draw nothing
    }
    else if(isStopped)
    {
        if(gameStateManager_->isGameWin())
        {
            painter->setPen(penYellow);
            painter->drawText(screenTextDisplayBoundingRect, Qt::AlignTop | Qt::AlignHCenter, "CONGRATULATIONS");
            painter->drawText(screenTextDisplayBoundingRect, Qt::AlignCenter, "FINAL SCORE : " + QString::number(scoreManager_.getScore()));
            painter->setPen(penBlue);
            painter->drawText(screenTextDisplayBoundingRect, Qt::AlignBottom | Qt::AlignHCenter, "PRESS SPACE TO CONTINUE");
        }
        else if(gameStateManager_->isGameLost())
        {
            painter->setPen(penRed);
            painter->drawText(screenTextDisplayBoundingRect, Qt::AlignTop | Qt::AlignHCenter, "GAME OVER");
            painter->setPen(penYellow);
            painter->drawText(screenTextDisplayBoundingRect, Qt::AlignCenter, "FINAL SCORE : " + QString::number(scoreManager_.getScore()));
            painter->setPen(penBlue);
            painter->drawText(screenTextDisplayBoundingRect, Qt::AlignBottom | Qt::AlignHCenter, "PRESS SPACE TO CONTINUE");
        }
        else
        {
            throw std::runtime_error("Unsupported game state, game stopped but no game result set");

        }
    }
    else
    {
        throw std::runtime_error("Unsupported game state");
    }
}
