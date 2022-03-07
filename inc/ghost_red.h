#pragma once

#include "ghost_base.h"

class GhostRed : public GhostBase
{
public:
    GhostRed();
    void reset() override;

private:
    QVector<std::string> getImagesUrls();

    static const int startingX_ = 307;
    static const int startingY_ = 252;
    static const int afterRespawnX_ = 307;
    static const int afterRespawnY_ = 318;
    static const int startTimeout_ = 0;
};
