#pragma once

#include "moving_object.h"
#include "movable_character.h"

class GhostTimingManager;

class AbstractGhost : public MovableCharacter
{
Q_OBJECT

public:
    AbstractGhost(const Coordinates& coordinates, Direction initialDirection, const std::chrono::seconds& moveOutOfTheStartingBoxTimeout);
    ~AbstractGhost() override = 0;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void advanceAnimation() override;
    void reset() override;

    void setScared();

    [[nodiscard]] bool isScared() const;
    [[nodiscard]] bool isScaredWhite() const;
    [[nodiscard]] bool isScaredBlue() const;

    [[nodiscard]] bool isSlowedDown() const
    { return isSlowedDown_; }

    [[nodiscard]] GhostTimingManager* getGhostTimingManager() const
    { return ghostTimingManager_; }

protected:
    void loadImages(const std::array<std::string, 12>& imagesUrls);

    bool canMoveAgain_{};

    bool isSlowedDown_{};

private slots:
    void resetCanMoveAgain();

private:
    enum class ScaredState
    {
        NO_SCARED, SCARED_BLUE, SCARED_WHITE
    } scaredState_;

    QPixmap left1Pixmap_, left2Pixmap_, up1Pixmap_, up2Pixmap_, down1Pixmap_, down2Pixmap_, right1Pixmap_, right2Pixmap_;
    QPixmap scaredBlue1Pixmap_, scaredBlue2Pixmap_;
    QPixmap scaredWhite1Pixmap_, scaredWhite2Pixmap_;

    int skippedMoves_{};

    //    QTimer currentStateTimer_;

    //    QTimer scaredBlueStateTimer_;
    //    QTimer scaredWhiteStateTimer_;

    GhostTimingManager* ghostTimingManager_{};
};
