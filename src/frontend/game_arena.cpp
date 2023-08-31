#include "game_arena.h"
#include "gui_config.h"
#include "config.h"

GameArena::GameArena(QWidget* parent, const Model& model) : QWidget(parent), model_(model)
{
    arenaPixmap = std::make_unique<QPixmap>(":/images/map.png");

    pacmanFrontend_ = std::make_unique<PacmanFrontend>(model_.getPacman());
    blueGhostFrontend_ = std::make_unique<BlueGhostFrontend>(model_.getBlueGhost());
    orangeGhostFrontend_ = std::make_unique<OrangeGhostFrontend>(model_.getOrangeGhost());
    purpleGhostFrontend_ = std::make_unique<PurpleGhostFrontend>(model_.getPurpleGhost());
    redGhostFrontend_ = std::make_unique<RedGhostFrontend>(model_.getRedGhost());

    screenTextDisplay_ = std::make_unique<ScreenTextDisplay>(model.getScreenTextManager());
}

void GameArena::paintEvent([[maybe_unused]] QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if(model_.getGameStateManager().isBeforeFirstRun())
    {
        drawArena(painter);
        drawCharacters(painter);
        drawBalls(painter);
        drawScreenTextDisplay(painter);
    }
    else if(model_.getGameStateManager().isStopped())
    {
        drawScreenTextDisplay(painter);
    }
    else if(model_.getGameStateManager().isRunning() || model_.getGameStateManager().isPaused())
    {
        drawArena(painter);
        drawCharacters(painter);
        drawBalls(painter);
    }
}

void GameArena::drawArena(QPainter& painter) const
{
    painter.drawPixmap(0, 0, 614, 740, *arenaPixmap);
}

void GameArena::drawCharacters(QPainter& painter) const
{
    drawPacman(painter);
    drawGhosts(painter);
}

void GameArena::drawBalls(QPainter& painter) const
{
    drawFoodballs(painter);
    drawPowerballs(painter);
}

void GameArena::drawGhosts(QPainter& painter) const
{
    drawGhost(painter, *blueGhostFrontend_);
    drawGhost(painter, *orangeGhostFrontend_);
    drawGhost(painter, *purpleGhostFrontend_);
    drawGhost(painter, *redGhostFrontend_);
}

void GameArena::drawPacman(QPainter& painter) const
{
    pacmanFrontend_->draw(painter);
}

void GameArena::drawGhost(QPainter& painter, const AbstractGhostFrontend& ghostFrontend) const
{
    ghostFrontend.draw(painter);
}

void GameArena::drawFoodballs(QPainter& painter) const
{
    for(const Foodball& foodball : model_.getBallItemsManager().getFoodballs())
    {
        drawFoodball(painter, foodball);
    }
}

void GameArena::drawPowerballs(QPainter& painter) const
{
    for(const Powerball& powerball : model_.getBallItemsManager().getPowerballs())
    {
        drawPowerball(painter, powerball);
    }
}

void GameArena::drawFoodball(QPainter& painter, const Foodball& foodball) const
{
    const Coordinates& coordinates = foodball.getCoordinates();

    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::white));
    painter.drawEllipse(coordinates.x_ + GuiConfig::Offsets::FOODBALL_X, coordinates.y_ + GuiConfig::Offsets::FOODBALL_Y, Config::Foodball::DIAMETER, Config::Foodball::DIAMETER);
}

void GameArena::drawPowerball(QPainter& painter, const Powerball& powerball) const
{
    const Coordinates& coordinates = powerball.getCoordinates();

    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::white));
    painter.drawEllipse(coordinates.x_ + GuiConfig::Offsets::POWERBALL_X, coordinates.y_ + GuiConfig::Offsets::POWERBALL_Y, Config::Powerball::DIAMETER, Config::Powerball::DIAMETER);
}

void GameArena::drawScreenTextDisplay(QPainter& painter)
{
    QRect screenTextDisplayBoundingRect(ScreenTextDisplay::X, ScreenTextDisplay::Y, ScreenTextDisplay::WIDTH, ScreenTextDisplay::HEIGHT);

    QPen penRed(Qt::red);
    QPen penYellow(Qt::yellow);
    QPen penBlue(Qt::blue);
    painter.setPen(penRed);

    QFont font = painter.font();
    font.setPointSize(ScreenTextDisplay::FONT_POINT_SIZE);
    painter.setFont(font);

    //TODO implement src result manager?
    GameResult gameResult = screenTextDisplay_->getScreenTextManager().getGameResult();

    if(gameResult == GameResult::WIN)
    {
        painter.setPen(penYellow);
        painter.drawText(screenTextDisplayBoundingRect, Qt::AlignTop | Qt::AlignHCenter, "CONGRATULATIONS");
        painter.drawText(screenTextDisplayBoundingRect, Qt::AlignCenter, "FINAL SCORE : " + QString::number(model_.getScoreManager().getScore()));
        painter.setPen(penBlue);
        painter.drawText(screenTextDisplayBoundingRect, Qt::AlignBottom | Qt::AlignHCenter, "PRESS SPACE TO RESTART");
    }
    else if(gameResult == GameResult::LOST)
    {
        painter.setPen(penRed);
        painter.drawText(screenTextDisplayBoundingRect, Qt::AlignTop | Qt::AlignHCenter, "GAME OVER");
        painter.setPen(penYellow);
        painter.drawText(screenTextDisplayBoundingRect, Qt::AlignCenter, "FINAL SCORE : " + QString::number(model_.getScoreManager().getScore()));
        painter.setPen(penBlue);
        painter.drawText(screenTextDisplayBoundingRect, Qt::AlignBottom | Qt::AlignHCenter, "PRESS SPACE TO RESTART");
    }
    else if(gameResult == GameResult::NO_RESULT_YET)
    {
        painter.drawText(screenTextDisplayBoundingRect, Qt::AlignCenter, "PRESS SPACE TO START");
    }
}
