#include "common_test_fixture.h"
#include "model/pacman.h"
#include "movement_manager.h"

class PacmanTest : public CommonTestFixture
{
protected:
    Pacman pacman_;;
};

TEST_F(PacmanTest, CreatePacman)
{
    EXPECT_EQ(pacman_.getCoordinates(), Coordinates(320, 514));
}

TEST_F(PacmanTest, MovePacman)
{
    PacmanMovementManager pacmanMovementManager;

    pacmanMovementManager.processMove(pacman_, pathPoints_);

    EXPECT_EQ(pacman_.getCoordinates(), Coordinates(319, 514));

    pacmanMovementManager.processMove(pacman_, pathPoints_);

    EXPECT_EQ(pacman_.getCoordinates(), Coordinates(318, 514));

    pacman_.setNextDirection(Direction::RIGHT);
    pacmanMovementManager.processMove(pacman_, pathPoints_);

    EXPECT_EQ(pacman_.getCoordinates(), Coordinates(319, 514));

    pacmanMovementManager.processMove(pacman_, pathPoints_);

    EXPECT_EQ(pacman_.getCoordinates(), Coordinates(320, 514));
}

TEST_F(PacmanTest, ResetPacman)
{
    PacmanMovementManager pacmanMovementManager;

    pacmanMovementManager.processMove(pacman_, pathPoints_);
    pacmanMovementManager.processMove(pacman_, pathPoints_);
    pacmanMovementManager.processMove(pacman_, pathPoints_);
    pacmanMovementManager.processMove(pacman_, pathPoints_);
    pacmanMovementManager.processMove(pacman_, pathPoints_);

    pacman_.reset();

    EXPECT_EQ(pacman_.getCoordinates(), Coordinates(320, 514));
}
