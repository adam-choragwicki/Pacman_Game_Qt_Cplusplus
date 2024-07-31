#include "common_test_fixture.h"
#include "model/ghosts/blue_ghost.h"
#include "model/ghosts/orange_ghost.h"
#include "model/ghosts/purple_ghost.h"
#include "model/ghosts/red_ghost.h"
#include "model/pacman.h"
#include "ghost_movement_manager.h"

class GhostTest : public CommonTestFixture
{
};

TEST_F(GhostTest, CreateBlueGhost)
{
    BlueGhost blueGhost(nullptr, nullptr);
    EXPECT_EQ(blueGhost.getCoordinates(), Coordinates(265, 318));
}

TEST_F(GhostTest, CreateOrangeGhost)
{
    OrangeGhost orangeGhost(nullptr, nullptr);
    EXPECT_EQ(orangeGhost.getCoordinates(), Coordinates(349, 318));
}

TEST_F(GhostTest, CreatePurpleGhost)
{
    PurpleGhost purpleGhost(nullptr, nullptr);
    EXPECT_EQ(purpleGhost.getCoordinates(), Coordinates(307, 318));
}

TEST_F(GhostTest, CreateRedGhost)
{
    RedGhost redGhost(nullptr, nullptr);
    EXPECT_EQ(redGhost.getCoordinates(), Coordinates(307, 252));
}

TEST_F(GhostTest, ResetGhost)
{
    Pacman pacman(nullptr);

    BlueGhost blueGhost(nullptr, nullptr);
    OrangeGhost orangeGhost(nullptr, nullptr);
    PurpleGhost purpleGhost(nullptr, nullptr);
    RedGhost redGhost(nullptr, nullptr);

    GhostMovementManager ghostMovementManager;

    ghostMovementManager.processMove(blueGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(orangeGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(purpleGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(redGhost, pacman.getCoordinates(), pathPoints_);

    ghostMovementManager.processMove(blueGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(orangeGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(purpleGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(redGhost, pacman.getCoordinates(), pathPoints_);

    ghostMovementManager.processMove(blueGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(orangeGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(purpleGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(redGhost, pacman.getCoordinates(), pathPoints_);

    ghostMovementManager.processMove(blueGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(orangeGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(purpleGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(redGhost, pacman.getCoordinates(), pathPoints_);

    blueGhost.reset();
    orangeGhost.reset();
    purpleGhost.reset();
    redGhost.reset();

    EXPECT_EQ(blueGhost.getCoordinates(), Coordinates(265, 318));
    EXPECT_EQ(orangeGhost.getCoordinates(), Coordinates(349, 318));
    EXPECT_EQ(purpleGhost.getCoordinates(), Coordinates(307, 318));
    EXPECT_EQ(redGhost.getCoordinates(), Coordinates(307, 252));
}
