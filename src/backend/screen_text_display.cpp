#include <QtGui/QPainter>
#include "screen_text_display.h"
#include "score_manager.h"
#include "model/game_state_manager.h"

ScreenTextDisplay::ScreenTextDisplay(const GameStateManager& gameStateManager, const ScreenTextManager& screenTextManager, const ScoreManager& scoreManager) :
        gameStateManager_(gameStateManager), screenTextManager_(screenTextManager), scoreManager_(scoreManager)
{}

void ScreenTextDisplay::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsTextItem::paint(painter, option, widget);

    QRect screenTextDisplayBoundingRect(ScreenTextDisplay::X, ScreenTextDisplay::Y, ScreenTextDisplay::WIDTH, ScreenTextDisplay::HEIGHT);

    QPen penRed(Qt::red);
    QPen penYellow(Qt::yellow);
    QPen penBlue(Qt::blue);
    painter->setPen(penRed);

    QFont font = painter->font();
    font.setPointSize(ScreenTextDisplay::FONT_POINT_SIZE);
    painter->setFont(font);

    //TODO implement src result manager?
    GameResult gameResult = getScreenTextManager().getGameResult();

    bool isBeforeFirstRun = gameStateManager_.isBeforeFirstRun();
    bool isPaused = gameStateManager_.isPaused();
    bool isRunning = gameStateManager_.isRunning();
    bool isStopped = gameStateManager_.isStopped();

    if(isBeforeFirstRun)
    {
        painter->drawText(screenTextDisplayBoundingRect, Qt::AlignCenter, "PRESS SPACE TO START");
    }
    else
    {
        if(gameResult == GameResult::WIN)
        {
            painter->setPen(penYellow);
            painter->drawText(screenTextDisplayBoundingRect, Qt::AlignTop | Qt::AlignHCenter, "CONGRATULATIONS");
            painter->drawText(screenTextDisplayBoundingRect, Qt::AlignCenter, "FINAL SCORE : " + QString::number(scoreManager_.getScore()));
            painter->setPen(penBlue);
            painter->drawText(screenTextDisplayBoundingRect, Qt::AlignBottom | Qt::AlignHCenter, "PRESS SPACE TO RESTART");
        }
        else if(gameResult == GameResult::LOST)
        {
            painter->setPen(penRed);
            painter->drawText(screenTextDisplayBoundingRect, Qt::AlignTop | Qt::AlignHCenter, "GAME OVER");
            painter->setPen(penYellow);
            painter->drawText(screenTextDisplayBoundingRect, Qt::AlignCenter, "FINAL SCORE : " + QString::number(scoreManager_.getScore()));
            painter->setPen(penBlue);
            painter->drawText(screenTextDisplayBoundingRect, Qt::AlignBottom | Qt::AlignHCenter, "PRESS SPACE TO RESTART");
        }
        //else if(gameResult == GameResult::NO_RESULT_YET)
        //{
        //      painter->drawText(screenTextDisplayBoundingRect, Qt::AlignCenter, "PRESS SPACE TO START");
        //}
    }
}