#pragma once

#include "ghost_base.h"

class GhostOrange : public GhostBase
{
public:
    explicit GhostOrange(const GameMap& gameMap);
    ~GhostOrange() override;

    void reset() override;

private:
    QVector<std::string> getImagesUrls();

    inline static const Coordinates startingCoordinates_ {349, 318};
    static constexpr std::chrono::seconds startTimeout_{2};
};
