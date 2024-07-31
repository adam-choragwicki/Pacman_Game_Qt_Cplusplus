#include "corner_wall_sw.h"
#include "pixmap_loader.h"

CornerWallSW::CornerWallSW(int x, int y, const QColor& color) : AbstractTile(x, y, color)
{
    pixmap_ = new QPixmap();

    const std::vector<PixmapLoader::PixmapEntry> pixmapEntries = {{pixmap_, ":/arena/corner_wall_NW.png"}};

    PixmapLoader::loadPixmaps(pixmapEntries);

    QTransform rotate90DegreesCounterClockwise;
    rotate90DegreesCounterClockwise.rotate(-90);

    *pixmap_ = pixmap_->transformed(rotate90DegreesCounterClockwise, Qt::TransformationMode::SmoothTransformation);
}
