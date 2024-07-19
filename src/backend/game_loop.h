#pragma once

#include <QObject>

class Model;
class QTimer;
class QGraphicsScene;
class MovingObject;
class Character;
class AbstractCreature;
class ProjectileManager;
class WorldMap;
class WorldBoundary;

class GameLoop : public QObject
{
Q_OBJECT

public:
    explicit GameLoop(Model& model);
    void start();

private slots:
    void execute();

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
//    QTimer* gameLoopTimer_{};
};
