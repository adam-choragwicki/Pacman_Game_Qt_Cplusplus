#pragma once

#include "common.h"

class ScreenTextManager
{
public:
    explicit ScreenTextManager();

    void setGameResult(GameResult gameResult)
    { gameResult_ = gameResult; }

    [[nodiscard]] GameResult getGameResult() const
    { return gameResult_; }

private:
    GameResult gameResult_;
};
