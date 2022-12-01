#pragma once

#include "screen_text_manager.h"

class ScreenTextDisplay
{
public:
    explicit ScreenTextDisplay(ScreenTextManager* screenTextManager);
    ~ScreenTextDisplay() = default;

    static const int WIDTH = 600;
    static const int HEIGHT = 200;
    static const int X = 614 / 2 - WIDTH / 2;
    static const int Y = 714 / 2 - HEIGHT / 2;
    static const int FONT_POINT_SIZE = 30;

    [[nodiscard]] ScreenTextManager* getScreenTextManager() const
    { return screenTextManager_; }

private:
    ScreenTextManager* screenTextManager_;
};
