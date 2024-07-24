#pragma once

class ScoreManager
{
public:
    ScoreManager() = default;

    [[nodiscard]] int getScore() const
    { return score_; }

    void increaseScoreForEatingStandardPellet()
    { score_ += 1; }

    void increaseScoreForEatingPowerPellet()
    { score_ += 100; }

    void increaseScoreForEatingGhost()
    { score_ += 200; }

    void resetScore()
    { score_ = 0; }

private:
    int score_ {};
};
