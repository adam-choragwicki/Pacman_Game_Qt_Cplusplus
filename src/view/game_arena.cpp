#include "view/game_arena.h"
#include "log_manager.h"
#include "view/gui_config.h"

using namespace GuiConfig;

GameArena::GameArena(QWidget* parent, Model* model) : QWidget(parent)
{
    model_ = model;

    arenaPixmap = std::make_unique<QPixmap>(":/images/map.png");

    pacmanFrontend_ = std::make_unique<PacmanFrontend>();
    blueGhostFrontend_ = std::make_unique<BlueGhostFrontend>(&model_->getBlueGhost());
    orangeGhostFrontend_ = std::make_unique<OrangeGhostFrontend>(&model_->getOrangeGhost());
    purpleGhostFrontend_ = std::make_unique<PurpleGhostFrontend>(&model_->getPurpleGhost());
    redGhostFrontend_ = std::make_unique<RedGhostFrontend>(&model_->getRedGhost());

    screenTextDisplay_ = std::make_unique<ScreenTextDisplay>(&model->getScreenTextManager());

    for(auto& foodball : model_->getBallItemsManager().getFoodballs())
    {
        foodballsFrontend_.emplace_back(&foodball);
    }

    for(auto& powerball : model_->getBallItemsManager().getPowerballs())
    {
        powerballsFrontend_.emplace_back(&powerball);
    }
}

void GameArena::paintEvent([[maybe_unused]] QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    GameState gameState = model_->getGameState();

    if(gameState == GameState::BEFORE_FIRST_RUN)
    {
        drawArena(painter);
        drawCharacters(painter);
        drawBalls(painter);
        drawScreenTextDisplay(painter);
    }
    else if(gameState == GameState::STOPPED)
    {
        drawScreenTextDisplay(painter);
    }
    else if(gameState == GameState::RUNNING || gameState == GameState::PAUSED)
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
    drawGhost(painter, blueGhostFrontend_.get());
    drawGhost(painter, orangeGhostFrontend_.get());
    drawGhost(painter, purpleGhostFrontend_.get());
    drawGhost(painter, redGhostFrontend_.get());
}

void GameArena::drawPacman(QPainter& painter) const
{
    const Coordinates& coordinates = model_->getPacman().getCoordinates();
    QRect boundingRect(coordinates.x_ + Offsets::PACMAN_X, coordinates.y_ + Offsets::PACMAN_Y, PacmanFrontend::DIAMETER, PacmanFrontend::DIAMETER);

    int animationState = model_->getPacman().getAnimationState();

    switch(model_->getPacman().getDirection())
    {
        case Direction::LEFT:
            if(animationState < 2 * PacmanFrontend::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, pacmanFrontend_->left1Pixmap_);
            }
            else if(animationState < 4 * PacmanFrontend::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, pacmanFrontend_->left2Pixmap_);
            }
            else if(animationState < 6 * PacmanFrontend::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, pacmanFrontend_->left3Pixmap_);
            }
            else if(animationState <= 8 * PacmanFrontend::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, pacmanFrontend_->left4Pixmap_);
            }
            break;

        case Direction::RIGHT:
            if(animationState < 2 * PacmanFrontend::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, pacmanFrontend_->right1Pixmap_);
            }
            else if(animationState < 4 * PacmanFrontend::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, pacmanFrontend_->right2Pixmap_);
            }
            else if(animationState < 6 * PacmanFrontend::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, pacmanFrontend_->right3Pixmap_);
            }
            else if(animationState <= 8 * PacmanFrontend::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, pacmanFrontend_->right4Pixmap_);
            }
            break;

        case Direction::UP:
            if(animationState < 2 * PacmanFrontend::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, pacmanFrontend_->up1Pixmap_);
            }
            else if(animationState < 4 * PacmanFrontend::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, pacmanFrontend_->up2Pixmap_);
            }
            else if(animationState < 6 * PacmanFrontend::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, pacmanFrontend_->up3Pixmap_);
            }
            else if(animationState <= 8 * PacmanFrontend::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, pacmanFrontend_->up4Pixmap_);
            }
            break;

        case Direction::DOWN:
            if(animationState < 2 * PacmanFrontend::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, pacmanFrontend_->down1Pixmap_);
            }
            else if(animationState < 4 * PacmanFrontend::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, pacmanFrontend_->down2Pixmap_);
            }
            else if(animationState < 6 * PacmanFrontend::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, pacmanFrontend_->down3Pixmap_);
            }
            else if(animationState <= 8 * PacmanFrontend::ANIMATION_SPEED_FACTOR)
            {
                painter.drawPixmap(boundingRect, pacmanFrontend_->down4Pixmap_);
            }
            break;

        case Direction::NONE:
            throw std::runtime_error("Painting Pacman Direction::NONE");
    }
}

void GameArena::drawGhost(QPainter& painter, AbstractGhostFrontend* ghostFrontend) const
{
    const Coordinates& coordinates = ghostFrontend->getAbstractGhost()->getCoordinates();

    QRect boundingRect(coordinates.x_ + Offsets::GHOST_X, coordinates.y_ + Offsets::GHOST_Y, AbstractGhostFrontend::DIAMETER, AbstractGhostFrontend::DIAMETER);

    AbstractGhost::ScaredState scaredState = ghostFrontend->getAbstractGhost()->getScaredState();

    int animationState = ghostFrontend->getAbstractGhost()->getAnimationState();

    if(scaredState == AbstractGhost::ScaredState::NO_SCARED)
    {
        switch(ghostFrontend->getAbstractGhost()->getDirection())
        {
            case Direction::LEFT:
                if(animationState == 0)
                {
                    painter.drawPixmap(boundingRect, ghostFrontend->left1Pixmap_);
                }
                else
                {
                    painter.drawPixmap(boundingRect, ghostFrontend->left2Pixmap_);
                }
                break;

            case Direction::RIGHT:
                if(animationState == 0)
                {
                    painter.drawPixmap(boundingRect, ghostFrontend->right1Pixmap_);
                }
                else
                {
                    painter.drawPixmap(boundingRect, ghostFrontend->right2Pixmap_);
                }
                break;

            case Direction::DOWN:
                if(animationState == 0)
                {
                    painter.drawPixmap(boundingRect, ghostFrontend->down1Pixmap_);
                }
                else
                {
                    painter.drawPixmap(boundingRect, ghostFrontend->down2Pixmap_);
                }
                break;

            case Direction::UP:
                if(animationState == 0)
                {
                    painter.drawPixmap(boundingRect, ghostFrontend->up1Pixmap_);
                }
                else
                {
                    painter.drawPixmap(boundingRect, ghostFrontend->up2Pixmap_);
                }
                break;

            case Direction::NONE:
                throw std::runtime_error("Painting Ghost Direction::NONE");
        }
    }
    else if(scaredState == AbstractGhost::ScaredState::SCARED_BLUE)
    {
        if(animationState == 0)
        {
            painter.drawPixmap(boundingRect, ghostFrontend->scaredBlue1Pixmap_);
        }
        else
        {
            painter.drawPixmap(boundingRect, ghostFrontend->scaredBlue2Pixmap_);
        }
    }
    else if(scaredState == AbstractGhost::ScaredState::SCARED_WHITE)
    {
        if(animationState == 0)
        {
            painter.drawPixmap(boundingRect, ghostFrontend->scaredWhite1Pixmap_);
        }
        else
        {
            painter.drawPixmap(boundingRect, ghostFrontend->scaredWhite2Pixmap_);
        }
    }
}

void GameArena::drawFoodballs(QPainter& painter) const
{
    for(auto& foodballFrontend : foodballsFrontend_)
    {
        drawFoodBall(painter, foodballFrontend);
    }
}

void GameArena::drawPowerballs(QPainter& painter) const
{
    for(auto& powerballFrontend : powerballsFrontend_)
    {
        drawPowerball(painter, powerballFrontend);
    }
}

void GameArena::drawFoodBall(QPainter& painter, const FoodballFrontend& foodballFrontend) const
{
    const Coordinates& coordinates = foodballFrontend.getBall()->getCoordinates();

    if(!foodballFrontend.getBall()->isEaten())
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(Qt::white));
        painter.drawEllipse(coordinates.x_ + Offsets::FOODBALL_X, coordinates.y_ + Offsets::FOODBALL_Y, FoodballFrontend::DIAMETER, FoodballFrontend::DIAMETER);
    }
}

void GameArena::drawPowerball(QPainter& painter, const PowerballFrontend& powerballFrontend) const
{
    const Coordinates& coordinates = powerballFrontend.getBall()->getCoordinates();

    if(!powerballFrontend.getBall()->isEaten())
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(Qt::white));
        painter.drawEllipse(coordinates.x_ + Offsets::POWERBALL_X, coordinates.y_ + Offsets::POWERBALL_Y, PowerballFrontend::DIAMETER, PowerballFrontend::DIAMETER);
    }
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

    GameResult gameResult = screenTextDisplay_->getScreenTextManager()->getGameResult();

    if(gameResult == GameResult::WIN)
    {
        painter.setPen(penYellow);
        painter.drawText(screenTextDisplayBoundingRect, Qt::AlignTop | Qt::AlignHCenter, "CONGRATULATIONS");
        painter.drawText(screenTextDisplayBoundingRect, Qt::AlignCenter, "FINAL SCORE : " + QString::number(model_->getScoreManager().getScore()));
        painter.setPen(penBlue);
        painter.drawText(screenTextDisplayBoundingRect, Qt::AlignBottom | Qt::AlignHCenter, "PRESS SPACE TO RESTART");
    }
    else if(gameResult == GameResult::LOST)
    {
        painter.setPen(penRed);
        painter.drawText(screenTextDisplayBoundingRect, Qt::AlignTop | Qt::AlignHCenter, "GAME OVER");
        painter.setPen(penYellow);
        painter.drawText(screenTextDisplayBoundingRect, Qt::AlignCenter, "FINAL SCORE : " + QString::number(model_->getScoreManager().getScore()));
        painter.setPen(penBlue);
        painter.drawText(screenTextDisplayBoundingRect, Qt::AlignBottom | Qt::AlignHCenter, "PRESS SPACE TO RESTART");
    }
    else if(gameResult == GameResult::NO_RESULT_YET)
    {
        painter.drawText(screenTextDisplayBoundingRect, Qt::AlignCenter, "PRESS SPACE TO START");
    }
}
