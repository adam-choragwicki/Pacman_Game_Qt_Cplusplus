#include "corner_wall_se.h"
#include "pixmap_loader.h"

CornerWallSE::CornerWallSE(int x, int y, const QColor& color) : AbstractTile(x, y, color)
{
    pixmap_ = new QPixmap();

    const std::vector<PixmapLoader::PixmapEntry> pixmapEntries = {{pixmap_, ":/arena/corner_wall_NW.png"}};

    PixmapLoader::loadPixmaps(pixmapEntries);

    QTransform rotate180Degrees;
    rotate180Degrees.rotate(180);

    *pixmap_ = pixmap_->transformed(rotate180Degrees, Qt::TransformationMode::SmoothTransformation);
}
