#pragma once

class ScoreManager
{
public:
    ScoreManager() = default;

    [[nodiscard]] int getScore() const
    { return score_; }

    void rewardPlayerForEatingFoodball()
    { score_ += 1; }

    void rewardPlayerForEatingGhost()
    { score_ += 200; }

    void rewardPlayerForEatingPowerball()
    { score_ += 100; }

    void resetScore()
    { score_ = 0; }

private:
    int score_ {};
};
