#pragma once

#include "movable_character.h"

#include <QTimer>

class AbstractGhost : public QObject, public MovableCharacter
{
Q_OBJECT

public:
    enum class ScaredState
    {
        NO_SCARED, SCARED_BLUE, SCARED_WHITE
    };

    AbstractGhost(const Coordinates& coordinates, std::chrono::seconds startTimeout, const GameMap& gameMap);
    ~AbstractGhost() override = default;

    virtual bool isItTimeToLeaveStartingBox()
    { return timeToLeaveStartingBox_; }

    void reset() override;
    void startMovement() override;
    void stopMovement() override;

    [[nodiscard]] ScaredState getScaredState() const
    { return scaredState_; }

    QTimer& getMovementTimer()
    { return movementTimer_; }

    [[nodiscard]] bool isInsideStartingBox() const;

    void setScaredState(ScaredState scaredState)
    { scaredState_ = scaredState; }

    void move(const Coordinates& pacmanCoordinates);
    void moveInsideStartingBox();
    void moveOutOfStartingBox();
    void scare();

private:
    void advanceAnimation() override;
    void reduceSpeed();
    void resetSpeed();

    const std::chrono::seconds scaredBlueTime{4};
    const std::chrono::seconds scaredWhiteTime{2};

    bool timeToLeaveStartingBox_;

    ScaredState scaredState_;

    QTimer movementTimer_;
    QTimer scaredBlueStateTimer_;
    QTimer scaredWhiteStateTimer_;
    QTimer startTimer_;

    const std::chrono::milliseconds NORMAL_SPEED{6};
    const std::chrono::milliseconds REDUCED_SPEED{50};

private slots:
    void transformToNoScared();
    void transformToScaredWhite();

    void setLeaveStartingBox()
    { timeToLeaveStartingBox_ = true; }
};
