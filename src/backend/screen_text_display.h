#pragma once

#include <QtWidgets/QGraphicsTextItem>
#include "screen_text_manager.h"

class GameStateManager;
class ScoreManager;

class ScreenTextDisplay : public QGraphicsTextItem
{
public:
    explicit ScreenTextDisplay(const GameStateManager& gameStateManager, const ScreenTextManager& screenTextManager, const ScoreManager& scoreManager);
    ~ScreenTextDisplay() override = default;
private:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
public:
    static const int WIDTH = 600;
    static const int HEIGHT = 200;
    static const int X = 614 / 2 - WIDTH / 2;
    static const int Y = 714 / 2 - HEIGHT / 2;
    static const int FONT_POINT_SIZE = 30;

    [[nodiscard]] const ScreenTextManager& getScreenTextManager() const
    { return screenTextManager_; }

private:
    const GameStateManager& gameStateManager_;
    const ScreenTextManager& screenTextManager_;
    const ScoreManager& scoreManager_;
};
