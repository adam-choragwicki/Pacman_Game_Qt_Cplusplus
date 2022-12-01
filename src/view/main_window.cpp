#include "view/main_window.h"

MainWindow::MainWindow(Model* model) : QDialog()
{
    model_ = model;

    setWindowTitle("Pacman");
    setFocus(Qt::ActiveWindowFocusReason);
    setFixedSize(614, 730);
    setPalette(QPalette(Qt::black));

    gameArena_ = std::make_unique<GameArena>(this, model);
    gameArena_->setFixedSize(614, 680);

    scoreDisplay_ = std::make_unique<ScoreDisplay>();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
        case Qt::Key_Left:
        case Qt::Key_A:
            emit keyPressedEvent(Key::LEFT);
            break;

        case Qt::Key_Right:
        case Qt::Key_D:
            emit keyPressedEvent(Key::RIGHT);
            break;

        case Qt::Key_Up:
        case Qt::Key_W:
            emit keyPressedEvent(Key::UP);
            break;

        case Qt::Key_Down:
        case Qt::Key_S:
            emit keyPressedEvent(Key::DOWN);
            break;

        case Qt::Key_P:
            emit keyPressedEvent(Key::PAUSE);
            break;

        case Qt::Key_Space:
            emit keyPressedEvent(Key::SPACE);
            break;
    }
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    if(model_->getGameState() != GameState::STOPPED)
    {
        drawScoreDisplay(painter);
    }
}

void MainWindow::drawScoreDisplay(QPainter& painter)
{
    QFont font = painter.font();
    font.setPointSize(ScoreDisplay::FONT_POINT_SIZE);

    painter.setPen(QPen(Qt::white));
    painter.setFont(font);

    QRect scoreDisplayBoundingRect(ScoreDisplay::X, ScoreDisplay::Y, ScoreDisplay::WIDTH, ScoreDisplay::HEIGHT);
    painter.drawText(scoreDisplayBoundingRect, Qt::AlignTop | Qt::AlignHCenter, "Score: " + QString::number(model_->getScoreManager().getScore()));
}
