#pragma once

#include "movable_character_interface.h"

#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>

class GhostBase : public QObject, public QGraphicsItem, public MovableCharacterInterface
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    enum class ScaredState
    {
        noScared,
        scaredBlue,
        scaredWhite
    };

    GhostBase(const Coordinates& coordinates, std::chrono::seconds startTimeout, const GameMap& gameMap);
    ~GhostBase() override;

    virtual bool isItTimeToLeaveStartingBox() {return timeToLeaveStartingBox_;}
    void reset() override;
    void startMovement() override;
    void stopMovement() override;

    [[nodiscard]] ScaredState getScaredState() const {return scaredState_;}
    QTimer& getMovementTimer() {return movementTimer_;}
    [[nodiscard]] bool isInsideStartingBox() const;

    void setScaredState(ScaredState scaredState) {scaredState_ = scaredState;}

    void move(const Coordinates& pacmanCoordinates);
    void moveInsideStartingBox();
    void moveOutOfStartingBox();
    void scare();

protected:
    void loadImages(const QVector<std::string>& imagesUrls);

private:
    [[nodiscard]] QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void advanceAnimation() override;
    void reduceSpeed();
    void resetSpeed();

    const std::chrono::seconds scaredBlueTime {4};
    const std::chrono::seconds scaredWhiteTime {2};

    bool timeToLeaveStartingBox_;

    ScaredState scaredState_;

    QTimer movementTimer_;
    QTimer scaredBlueStateTimer_;
    QTimer scaredWhiteStateTimer_;
    QTimer startTimer_;

    QPixmap left1Pixmap_, left2Pixmap_, up1Pixmap_, up2Pixmap_, down1Pixmap_, down2Pixmap_, right1Pixmap_, right2Pixmap_;
    QPixmap scaredBlue1Pixmap_, scaredBlue2Pixmap_;
    QPixmap scaredWhite1Pixmap_, scaredWhite2Pixmap_;

private slots:
    void transformToNoScared();
    void transformToScaredWhite();

    void setLeaveStartingBox() {timeToLeaveStartingBox_ = true;}
};
