#include "common_test_fixture.h"
#include "pacman.h"
#include "game_map.h"

class PacmanTest : public CommonTestFixture
{
protected:
    Pacman pacman_;
    GameMap gameMap_;
};

TEST_F(PacmanTest, CreatePacman)
{
    EXPECT_EQ(pacman_.getX(), 320);
    EXPECT_EQ(pacman_.getY(), 514);
}

TEST_F(PacmanTest, MovePacman)
{
    EXPECT_EQ(pacman_.getX(), 320);
    EXPECT_EQ(pacman_.getY(), 514);

    pacman_.move();

    EXPECT_EQ(pacman_.getX(), 319);
    EXPECT_EQ(pacman_.getY(), 514);

    pacman_.setNextDirection(Direction::right);
    pacman_.move();

    EXPECT_EQ(pacman_.getX(), 320);
    EXPECT_EQ(pacman_.getY(), 514);
}

TEST_F(PacmanTest, ResetPacman)
{
    EXPECT_EQ(pacman_.getX(), 320);
    EXPECT_EQ(pacman_.getY(), 514);

    pacman_.move();
    pacman_.move();
    pacman_.move();
    pacman_.move();
    pacman_.move();

    pacman_.reset();

    EXPECT_EQ(pacman_.getX(), 320);
    EXPECT_EQ(pacman_.getY(), 514);
}
