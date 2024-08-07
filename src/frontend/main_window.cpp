#include "main_window.h"
#include "graphics_view.h"
#include "model/model.h"
#include "spdlog/spdlog.h"

#include <QScreen>
#include <QGuiApplication>

MainWindow::MainWindow(const Model& model) : QMainWindow(), model_(model)
{
    spdlog::debug("Initializing view");

    setWindowTitle("Pacman");
    setFocus(Qt::ActiveWindowFocusReason);

    graphicsView_ = std::make_unique<GraphicsView>(model_.getScene(), *model.getWhatToDrawManager(), this);

    const int WINDOW_WIDTH = 614;
    const int WINDOW_HEIGHT = 730;

    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    setPalette(QPalette(Qt::black));

    setCentralWidget(graphicsView_.get());

    centerOnPrimaryScreen();

    viewportUpdateTimer_ = std::make_unique<QTimer>(this);
    viewportUpdateTimer_->setTimerType(Qt::PreciseTimer);
    viewportUpdateTimer_->setInterval(VIEWPORT_UPDATE_INTERVAL);
    viewportUpdateTimer_->start();
}

void MainWindow::centerOnPrimaryScreen()
{
    QScreen* primaryScreen = QGuiApplication::primaryScreen();
    centerOnScreen(primaryScreen);
}

void MainWindow::centerOnScreen(QScreen* screen)
{
    setScreen(screen);
    const QRect screenRect = screen->availableGeometry();
    const QRect widgetRect({}, frameSize().boundedTo(screenRect.size()));
    move(screenRect.center() - widgetRect.center());
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    emit keyPressedEvent(event);
}

void MainWindow::updateViewport(const QList<QRectF>& dirtyRegions)
{
    graphicsView_->updateViewport(dirtyRegions);
}
