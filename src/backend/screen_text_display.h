#pragma once

#include <QtWidgets/QGraphicsTextItem>

class GameStateManager;
class ScoreManager;

class ScreenTextDisplay : public QGraphicsTextItem
{
public:
    explicit ScreenTextDisplay(const ScoreManager& scoreManager);
    ~ScreenTextDisplay() override = default;

    static const int WIDTH = 600;
    static const int HEIGHT = 200;
    static const int X = 614 / 2 - WIDTH / 2;
    static const int Y = 714 / 2 - HEIGHT / 2;
    static const int FONT_POINT_SIZE = 30;

    void setGameStateManager(GameStateManager* gameStateManager)
    { gameStateManager_ = gameStateManager; }

private:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    //    const GameStateManager& gameStateManager_;
    const ScoreManager& scoreManager_;

    GameStateManager* gameStateManager_{};
};
