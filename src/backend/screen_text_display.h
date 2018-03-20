#pragma once

#include <QtWidgets/QGraphicsTextItem>

class GameManager;
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

    void setGameManager(GameManager* gameManager)
    { gameManager_ = gameManager; }

private:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    const ScoreManager& scoreManager_;
    GameManager* gameManager_{};
};
