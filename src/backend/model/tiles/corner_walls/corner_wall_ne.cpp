#include "corner_wall_ne.h"
#include "pixmap_loader.h"

CornerWallNE::CornerWallNE(int x, int y, const QColor& color) : AbstractTile(x, y, color)
{
    pixmap_ = new QPixmap();

    const std::vector<PixmapLoader::PixmapEntry> pixmapEntries = {{pixmap_, ":/arena/corner_wall_NW.png"}};

    PixmapLoader::loadPixmaps(pixmapEntries);

    QTransform rotate90DegreesClockwise;
    rotate90DegreesClockwise.rotate(+90);

    *pixmap_ = pixmap_->transformed(rotate90DegreesClockwise, Qt::TransformationMode::SmoothTransformation);
}
