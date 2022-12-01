#include "common_test_fixture.h"
#include "pacman.h"

class PacmanTest : public CommonTestFixture
{
protected:
    Pacman pacman_{gameMap_};
};

TEST_F(PacmanTest, CreatePacman)
{
    EXPECT_EQ(pacman_.getCoordinates(), Coordinates(320, 514));
}

TEST_F(PacmanTest, MovePacman)
{
    pacman_.move();

    EXPECT_EQ(pacman_.getCoordinates(), Coordinates(319, 514));

    pacman_.setNextDirection(Direction::RIGHT);
    pacman_.move();

    EXPECT_EQ(pacman_.getCoordinates(), Coordinates(320, 514));
}

TEST_F(PacmanTest, ResetPacman)
{
    pacman_.move();
    pacman_.move();
    pacman_.move();
    pacman_.move();
    pacman_.move();

    pacman_.reset();

    EXPECT_EQ(pacman_.getCoordinates(), Coordinates(320, 514));
}
