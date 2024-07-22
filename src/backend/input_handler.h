#pragma once

#include <QObject>

class Model;
class QKeyEvent;

class InputHandler : public QObject
{
Q_OBJECT

signals:
    void startOrRestartGameRequested();
    void togglePauseRequested();

public:
    explicit InputHandler(Model& model);

public slots:
    void processKeyPressedEvent(QKeyEvent* keyEvent);

private:
    Model& model_;
};
