#include "game_window.h"
#include "ui_game_window.h"
#include "drawer.h"
#include "common.h"

GameWindow::GameWindow(QWidget* parent) : QDialog(parent), ui_(new Ui::GameWindow)
{
    ui_->setupUi(this);
    setWindowTitle("Pacman");
    setFocus(Qt::ActiveWindowFocusReason);

    initializeGameplayAreaScene();
    Drawer::drawGameArena();

    gameEngine_ = std::make_unique<GameEngine>();
    QObject::connect(gameEngine_.get(), &GameEngine::restartGame, this, &GameWindow::processRestartGameSlot);
}

GameWindow::~GameWindow()
{
    delete ui_;
}

void GameWindow::initializeGameplayAreaScene()
{
    const int sceneWidth = 614;
    const int sceneHeight = 740;

    ui_->graphicsView->setScene(&scene_);
    scene_.setSceneRect(0, 0, sceneWidth, sceneHeight);
    ui_->graphicsView->setSceneRect(scene_.sceneRect());

    ui_->graphicsView->setRenderHint(QPainter::Antialiasing);

    Drawer::setScene(&scene_);
}

/*Supports pacman movement using WSAD and directional keys*/
void GameWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Left:
    case Qt::Key_A:
        gameEngine_->processKey(Key::left);
        break;

    case Qt::Key_Right:
    case Qt::Key_D:
        gameEngine_->processKey(Key::right);
        break;

    case Qt::Key_Up:
    case Qt::Key_W:
        gameEngine_->processKey(Key::up);
        break;

    case Qt::Key_Down:
    case Qt::Key_S:
        gameEngine_->processKey(Key::down);
        break;

    case Qt::Key_P:
        gameEngine_->processKey(Key::pause);
        break;

    case Qt::Key_Space:
        gameEngine_->processKey(Key::space);
        break;
    }
}

void GameWindow::processRestartGameSlot()
{
    gameEngine_.reset();
    gameEngine_ = std::make_unique<GameEngine>();
    QObject::connect(gameEngine_.get(), &GameEngine::restartGame, this, &GameWindow::processRestartGameSlot);
}
