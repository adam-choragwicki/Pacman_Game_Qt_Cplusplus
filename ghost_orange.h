#pragma once

#include "ghost_base.h"

class GhostOrange : public GhostBase
{
public:
    GhostOrange();
    void reset() override;

private:
    QVector<QString> getImagesUrls();

    static const int startingX_ = 349;
    static const int startingY_ = 318;
    static const int startTimeout_ = 2000;
};
