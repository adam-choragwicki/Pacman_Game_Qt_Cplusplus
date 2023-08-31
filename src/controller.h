#pragma once

#include "model/model.h"
#include "main_window.h"

class Controller : public QObject
{
Q_OBJECT

public slots:
    void processKeyPressedEvent(QKeyEvent* keyEvent);
    void frontendUpdateHandler();

public:
    Controller(Model& model, MainWindow& view);

    void subscribeToKeyEvents();

    void startGame();
    void endGame(GameResult gameResult);
    void togglePause();

private slots:
    void pacmanMovementHandler();
    void ghostMovementHandler(AbstractGhost& ghost);

private:
    Model& model_;
    MainWindow& view_;

    void startAllCharacters();
    void stopAllCharacters();
};
