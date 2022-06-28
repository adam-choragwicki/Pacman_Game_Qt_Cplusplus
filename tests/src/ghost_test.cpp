#include "common_test_fixture.h"
#include "ghosts/ghost_blue.h"
#include "ghosts/ghost_orange.h"
#include "ghosts/ghost_purple.h"
#include "ghosts/ghost_red.h"
#include "pacman.h"

class GhostTest : public CommonTestFixture
{
protected:
    GhostBlue ghostBlue_{gameMap_};
    GhostOrange ghostOrange_{gameMap_};
    GhostPurple ghostPurple_{gameMap_};
    GhostRed ghostRed_{gameMap_};
};

TEST_F(GhostTest, CreateGhosts)
{
    EXPECT_EQ(ghostBlue_.getCoordinates(), Coordinates(265, 318));
    EXPECT_EQ(ghostOrange_.getCoordinates(), Coordinates(349, 318));
    EXPECT_EQ(ghostPurple_.getCoordinates(), Coordinates(307, 318));
    EXPECT_EQ(ghostRed_.getCoordinates(), Coordinates(307, 252));
}

TEST_F(GhostTest, ResetGhost)
{
    Pacman pacman{gameMap_};

    ghostBlue_.move(pacman.getCoordinates());
    ghostOrange_.move(pacman.getCoordinates());
    ghostPurple_.move(pacman.getCoordinates());
    ghostRed_.move(pacman.getCoordinates());

    ghostBlue_.move(pacman.getCoordinates());
    ghostOrange_.move(pacman.getCoordinates());
    ghostPurple_.move(pacman.getCoordinates());
    ghostRed_.move(pacman.getCoordinates());

    ghostBlue_.move(pacman.getCoordinates());
    ghostOrange_.move(pacman.getCoordinates());
    ghostPurple_.move(pacman.getCoordinates());
    ghostRed_.move(pacman.getCoordinates());

    ghostBlue_.move(pacman.getCoordinates());
    ghostOrange_.move(pacman.getCoordinates());
    ghostPurple_.move(pacman.getCoordinates());
    ghostRed_.move(pacman.getCoordinates());

    ghostBlue_.reset();
    ghostOrange_.reset();
    ghostPurple_.reset();
    ghostRed_.reset();

    EXPECT_EQ(ghostBlue_.getCoordinates(), Coordinates(265, 318));
    EXPECT_EQ(ghostOrange_.getCoordinates(), Coordinates(349, 318));
    EXPECT_EQ(ghostPurple_.getCoordinates(), Coordinates(307, 318));
    EXPECT_EQ(ghostRed_.getCoordinates(), Coordinates(307, 318));
}
