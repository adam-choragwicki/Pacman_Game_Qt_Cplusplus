#pragma once

#include "model/model.h"
#include "main_window.h"

class InputHandler;

class Controller : public QObject
{
Q_OBJECT

public slots:
    void viewportUpdateHandler();

public:
    Controller(Model& model, MainWindow& view);

    void subscribeToKeyEvents();
    void initializeFrontendEvents();

private:
    Model& model_;
    MainWindow& view_;

    InputHandler* inputHandler_{};
    GameLoop* gameLoop_{};
};
