#include "common_test_fixture.h"
#include "ghost_blue.h"
#include "ghost_orange.h"
#include "ghost_purple.h"
#include "ghost_red.h"
#include "game_map.h"
#include "pacman.h"

class GhostTest : public CommonTestFixture
{
protected:
    GhostBlue ghostBlue_;
    GhostOrange ghostOrange_;
    GhostPurple ghostPurple_;
    GhostRed ghostRed_;
    GameMap gameMap_;
};

TEST_F(GhostTest, CreateGhosts)
{
    EXPECT_EQ(ghostBlue_.getX(), 265);
    EXPECT_EQ(ghostBlue_.getY(), 318);

    EXPECT_EQ(ghostOrange_.getX(), 349);
    EXPECT_EQ(ghostOrange_.getY(), 318);

    EXPECT_EQ(ghostPurple_.getX(), 307);
    EXPECT_EQ(ghostPurple_.getY(), 318);

    EXPECT_EQ(ghostRed_.getX(), 307);
    EXPECT_EQ(ghostRed_.getY(), 252);
}

TEST_F(GhostTest, ResetGhost)
{
    Pacman pacman;

    ghostBlue_.move(pacman.getX(), pacman.getY());
    ghostOrange_.move(pacman.getX(), pacman.getY());
    ghostPurple_.move(pacman.getX(), pacman.getY());
    ghostRed_.move(pacman.getX(), pacman.getY());

    ghostBlue_.move(pacman.getX(), pacman.getY());
    ghostOrange_.move(pacman.getX(), pacman.getY());
    ghostPurple_.move(pacman.getX(), pacman.getY());
    ghostRed_.move(pacman.getX(), pacman.getY());

    ghostBlue_.move(pacman.getX(), pacman.getY());
    ghostOrange_.move(pacman.getX(), pacman.getY());
    ghostPurple_.move(pacman.getX(), pacman.getY());
    ghostRed_.move(pacman.getX(), pacman.getY());

    ghostBlue_.move(pacman.getX(), pacman.getY());
    ghostOrange_.move(pacman.getX(), pacman.getY());
    ghostPurple_.move(pacman.getX(), pacman.getY());
    ghostRed_.move(pacman.getX(), pacman.getY());

    ghostBlue_.reset();
    ghostOrange_.reset();
    ghostPurple_.reset();
    ghostRed_.reset();

    EXPECT_EQ(ghostBlue_.getX(), 265);
    EXPECT_EQ(ghostBlue_.getY(), 318);

    EXPECT_EQ(ghostOrange_.getX(), 349);
    EXPECT_EQ(ghostOrange_.getY(), 318);

    EXPECT_EQ(ghostPurple_.getX(), 307);
    EXPECT_EQ(ghostPurple_.getY(), 318);

    EXPECT_EQ(ghostRed_.getX(), 307);
    EXPECT_EQ(ghostRed_.getY(), 318);
}
