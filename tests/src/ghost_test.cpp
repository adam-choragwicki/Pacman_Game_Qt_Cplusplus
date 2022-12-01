#include "common_test_fixture.h"
#include "ghosts/blue_ghost.h"
#include "ghosts/orange_ghost.h"
#include "ghosts/purple_ghost.h"
#include "ghosts/red_ghost.h"
#include "pacman.h"

class GhostTest : public CommonTestFixture
{
protected:
    BlueGhost blueGhost_{gameMap_};
    OrangeGhost orangeGhost_{gameMap_};
    PurpleGhost purpleGhost_{gameMap_};
    RedGhost redGhost_{gameMap_};
};

TEST_F(GhostTest, CreateGhosts)
{
    EXPECT_EQ(blueGhost_.getCoordinates(), Coordinates(265, 318));
    EXPECT_EQ(orangeGhost_.getCoordinates(), Coordinates(349, 318));
    EXPECT_EQ(purpleGhost_.getCoordinates(), Coordinates(307, 318));
    EXPECT_EQ(redGhost_.getCoordinates(), Coordinates(307, 252));
}

TEST_F(GhostTest, ResetGhost)
{
    Pacman pacman{gameMap_};

    blueGhost_.move(pacman.getCoordinates());
    orangeGhost_.move(pacman.getCoordinates());
    purpleGhost_.move(pacman.getCoordinates());
    redGhost_.move(pacman.getCoordinates());

    blueGhost_.move(pacman.getCoordinates());
    orangeGhost_.move(pacman.getCoordinates());
    purpleGhost_.move(pacman.getCoordinates());
    redGhost_.move(pacman.getCoordinates());

    blueGhost_.move(pacman.getCoordinates());
    orangeGhost_.move(pacman.getCoordinates());
    purpleGhost_.move(pacman.getCoordinates());
    redGhost_.move(pacman.getCoordinates());

    blueGhost_.move(pacman.getCoordinates());
    orangeGhost_.move(pacman.getCoordinates());
    purpleGhost_.move(pacman.getCoordinates());
    redGhost_.move(pacman.getCoordinates());

    blueGhost_.reset();
    orangeGhost_.reset();
    purpleGhost_.reset();
    redGhost_.reset();

    EXPECT_EQ(blueGhost_.getCoordinates(), Coordinates(265, 318));
    EXPECT_EQ(orangeGhost_.getCoordinates(), Coordinates(349, 318));
    EXPECT_EQ(purpleGhost_.getCoordinates(), Coordinates(307, 318));
    EXPECT_EQ(redGhost_.getCoordinates(), Coordinates(307, 318));
}
