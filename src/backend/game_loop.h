#pragma once

#include <QObject>

class Model;
class QTimer;

class AbstractGhost;

class Pacman;

class BlueGhost;
class OrangeGhost;
class PurpleGhost;
class RedGhost;

class GameManager;
class GhostMovementManager;

class ScoreManager;

class PelletsManager;

enum class GameResult;

class GameLoop : public QObject
{
Q_OBJECT

signals:
    void endGame(GameResult gameResult);

public:
    explicit GameLoop(Model& model);
    void start();
    void stop();
    void resume();

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

    GhostMovementManager& ghostMovementManager_;

    ScoreManager& scoreManager_;

    PelletsManager& pelletsManager_;

    QTimer* gameLoopTimer_{};

//    bool firstStartInCurrentGame_{};
};
