#include "horizontal_wall.h"
#include "pixmap_loader.h"

HorizontalWall::HorizontalWall(int x, int y, const QColor& color) : AbstractTile(x, y, color)
{
    pixmap_ = new QPixmap();

    const std::vector<PixmapLoader::PixmapEntry> pixmapEntries = {{pixmap_, ":/arena/vertical_wall.png"}};

    PixmapLoader::loadPixmaps(pixmapEntries);

    QTransform rotate90DegreesClockwise;
    rotate90DegreesClockwise.rotate(+90);

    *pixmap_ = pixmap_->transformed(rotate90DegreesClockwise, Qt::TransformationMode::SmoothTransformation);
}
