#pragma once

#include <QObject>

class Model;
class QTimer;
class QGraphicsScene;
class MovingObject;

class AbstractGhost;

class Pacman;

class BlueGhost;
class OrangeGhost;
class PurpleGhost;
class RedGhost;

class GameStateManager;
class GhostMovementManager;

class ScoreManager;

class BallItemsManager;

class GameLoop : public QObject
{
Q_OBJECT

public:
    explicit GameLoop(Model& model);
    void start();
    void stop();

private slots:
    void execute();

    void pacmanMovementHandler();
    void ghostMovementHandler(AbstractGhost& ghost);

private:
    Model& model_;

    Pacman& pacman_;

    BlueGhost& blueGhost_;
    OrangeGhost& orangeGhost_;
    PurpleGhost& purpleGhost_;
    RedGhost& redGhost_;

    std::array<AbstractGhost*, 4> ghosts_;

    GameStateManager& gameStateManager_;

    GhostMovementManager& ghostMovementManager_;

    ScoreManager& scoreManager_;

    BallItemsManager& ballItemsManager_;

    QTimer* gameLoopTimer_{};

    bool firstStartInCurrentGame_{};
};
