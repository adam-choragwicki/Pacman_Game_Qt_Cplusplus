#pragma once

class ScoreManager
{
public:
    ScoreManager() = default;

    [[nodiscard]] int getScore() const
    { return score_; }

    void increaseScoreForEatingFoodball()
    { score_ += 1; }

    void increaseScoreForEatingGhost()
    { score_ += 200; }

    void increaseScoreForEatingPowerball()
    { score_ += 100; }

    void resetScore()
    { score_ = 0; }

private:
    int score_ {};
};
