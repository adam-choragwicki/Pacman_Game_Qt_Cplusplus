#pragma once

#include "ghost_base.h"

class GhostPurple : public GhostBase
{
public:
    GhostPurple();
    void reset() override;

private:
    QVector<std::string> getImagesUrls();

    static const int startingX_ = 307;
    static const int startingY_ = 318;
    static const int startTimeout_ = 1000;
};
