#pragma once

class ScoreManager
{
public:
    ScoreManager() = default;

    void reset()
    { score_ = 0; }

    [[nodiscard]] int getScore() const
    { return score_; }

    void increaseScoreForEatingStandardPellet()
    { score_ += 1; }

    void increaseScoreForEatingPowerPellet()
    { score_ += 100; }

    void increaseScoreForEatingGhost()
    { score_ += 200; }

private:
    int score_{};
};
