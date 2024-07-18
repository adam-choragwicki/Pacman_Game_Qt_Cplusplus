#include "main_window.h"
#include "score_display.h"
#include "graphics_view.h"
#include <QScreen>
#include <QGuiApplication>

MainWindow::MainWindow(const Model& model) : QMainWindow(), model_(model)//, gameArena_(this, model)
{
    setWindowTitle("Pacman");
    setFocus(Qt::ActiveWindowFocusReason);
    setFixedSize(614, 730);
    setPalette(QPalette(Qt::black));

    //    gameArena_.setFixedSize(614, 680);

    graphicsView_ = new GraphicsView(model_.getScene());

    setCentralWidget(graphicsView_);

    centerOnPrimaryScreen();
}

void MainWindow::centerOnPrimaryScreen()
{
    QScreen* primaryScreen = QGuiApplication::primaryScreen();
    centerOnScreen(primaryScreen);
}

void MainWindow::centerOnScreen(QScreen* screen)
{
    //spdlog::debug("Screen name: " + screen->name().toStdString());
    //spdlog::debug("Screen manufacturer: " + screen->manufacturer().toStdString());
    //spdlog::debug("Screen model: " + screen->model().toStdString());

    setScreen(screen);
    const QRect screenRect = screen->availableGeometry();
    const QRect widgetRect({}, frameSize().boundedTo(screenRect.size()));
    move(screenRect.center() - widgetRect.center());
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    emit keyPressedEvent(event);
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    if(!model_.getGameStateManager().isStopped())
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
    painter.drawText(scoreDisplayBoundingRect, Qt::AlignTop | Qt::AlignHCenter, "Score: " + QString::number(model_.getScoreManager().getScore()));
}

void MainWindow::updateViewport()
{
    graphicsView_->updateViewport();
}
