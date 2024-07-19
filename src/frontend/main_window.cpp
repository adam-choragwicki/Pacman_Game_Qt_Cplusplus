#include "main_window.h"
#include "score_display.h"
#include "graphics_view.h"
#include "model/model.h"

#include <QScreen>
#include <QGuiApplication>

MainWindow::MainWindow(const Model& model) : QMainWindow(), model_(model)//, gameArena_(this, model)
{
    setWindowTitle("Pacman");
    setFocus(Qt::ActiveWindowFocusReason);

    graphicsView_ = new GraphicsView(model_.getScene());

    const int WINDOW_WIDTH = 614;
    const int WINDOW_HEIGHT = 730;

    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

//    setPalette(QPalette(Qt::black));

    //    gameArena_.setFixedSize(614, 680);


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

void MainWindow::updateViewport()
{
    graphicsView_->updateViewport();
}
