#pragma once

#include "model/model.h"
#include "main_window.h"

class InputHandler;

class Controller : public QObject
{
Q_OBJECT

public slots:
    void viewportUpdateHandler();

    void startGame();
    void togglePause();

public:
    Controller(Model& model, MainWindow& view);

    void subscribeToKeyEvents();
    void initializeFrontendEvents();

    void endGame(GameResult gameResult);

private slots:
    void pacmanMovementHandler();
    void ghostMovementHandler(AbstractGhost& ghost);

private:
    Model& model_;
    MainWindow& view_;

    InputHandler* inputHandler_{};

    void startAllCharacters();
    void stopAllCharacters();
};
