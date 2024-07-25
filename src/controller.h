#pragma once

#include "model/model.h"
#include "main_window.h"
#include "input_handler.h"
#include "game_loop.h"
#include "game_manager.h"

class Controller : public QObject
{
Q_OBJECT

public slots:
    void viewportUpdateHandler();

public:
    Controller(Model& model, MainWindow& view);

    void subscribeToKeyEvents();
    void initializeFrontendEvents();

private slots:
    void updateDirtyRegion(const QList<QRectF>& dirtyRegions);

private:
    Model& model_;
    MainWindow& view_;

    std::unique_ptr<InputHandler> inputHandler_;
    std::unique_ptr<GameLoop> gameLoop_;
    std::unique_ptr<GameManager> gameManager_;

    QList<QRectF> dirtyRegions_;
//    QRect dirtyRegion_;
};
