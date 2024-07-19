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

class GameLoop : public QObject
{
Q_OBJECT

public slots:
    void togglePause();

public:
    explicit GameLoop(Model& model);
    void start();

private slots:
    void execute();

    void pacmanMovementHandler();
    void ghostMovementHandler(AbstractGhost& ghost);

private:
    Model& model_;
    //    QGraphicsScene& scene_;
    //
    //    AbstractGhost* ghost1_{};
    //    AbstractGhost* ghost2_{};
    //    AbstractGhost* ghost3_{};
    //    AbstractGhost* ghost4_{};

    Pacman& pacman_;

    BlueGhost& blueGhost_;
    OrangeGhost& orangeGhost_;
    PurpleGhost& purpleGhost_;
    RedGhost& redGhost_;

    std::array<AbstractGhost*, 4> ghosts_;

    GameStateManager& gameStateManager_;

    GhostMovementManager& ghostMovementManager_;

    QTimer* gameLoopTimer_{};
};
