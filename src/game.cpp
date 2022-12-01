#include "game.h"
#include "log_manager.h"

Game::Game()
{
    model_ = std::make_unique<Model>();
    view_ = std::make_unique<MainWindow>(model_.get());
    controller_ = std::make_unique<Controller>(model_.get(), view_.get());

    subscribeToRestartEvent();
    view_->show();
}

void Game::subscribeToRestartEvent()
{
    connect(controller_.get(), &Controller::restartEvent, this, &Game::processRestartEvent);
}

void Game::processRestartEvent()
{
    model_->reset();
    controller_->startGame();
}
