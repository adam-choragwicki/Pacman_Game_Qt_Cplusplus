#pragma once

#include "ghost_base.h"

class GhostBlue : public GhostBase
{
public:
    explicit GhostBlue(const GameMap& gameMap);
    ~GhostBlue() override;

    void reset() override;

private:
    QVector<std::string> getImagesUrls();

    inline static const Coordinates startingCoordinates_ {265, 318};
    static constexpr std::chrono::seconds startTimeout_{3};
};
