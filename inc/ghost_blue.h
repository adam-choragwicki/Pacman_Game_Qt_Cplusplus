#pragma once

#include "ghost_base.h"

class GhostBlue : public GhostBase
{
public:
    GhostBlue();
    void reset() override;

private:
    QVector<std::string> getImagesUrls();

    static const int startingX_ = 265;
    static const int startingY_ = 318;
    static const int startTimeout_ = 3000;
};
