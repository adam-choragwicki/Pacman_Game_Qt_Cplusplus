#pragma once

#include "model.h"
#include "view/main_window.h"

class Controller : public QObject
{
Q_OBJECT

signals:
    void restartEvent();

public slots:
    void processKeyPressedEvent(Key key);
    void frontendUpdateHandler();

public:
    Controller(Model* model, MainWindow* view);

    void subscribeToKeyEvents();

    void startGame();
    void endGame(GameResult gameResult);
    void togglePause();

private slots:
    void pacmanMovementHandler();
    void ghostMovementHandler(AbstractGhost* ghost);

private:
    Model* model_;
    MainWindow* view_;

    QTimer frontendUpdateTimer_;
    const std::chrono::milliseconds FRONTEND_UPDATE_FREQUENCY{16};
};
