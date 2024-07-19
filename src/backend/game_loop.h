#pragma once

#include <QObject>

class Model;
class QTimer;
class QGraphicsScene;
class MovingObject;
class Character;
class WorldMap;
class WorldBoundary;

class AbstractGhost;

class Pacman;

class BlueGhost;
class OrangeGhost;
class PurpleGhost;
class RedGhost;

class GhostMovementManager;

class GameLoop : public QObject
{
Q_OBJECT

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
    //    const std::vector<MovingObject*>& movingObjects_;
    //    Character& character_;
    //    const std::vector<AbstractCreature*>& creatures_;
    //
    //    ProjectileManager& projectileManager_;
    //
    //    const WorldMap& worldMap_;
    //    const std::vector<WorldBoundary*>& worldBoundaries_;
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

    GhostMovementManager& ghostMovementManager_;

    QTimer* gameLoopTimer_{};
};
