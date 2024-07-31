#include "vertical_wall.h"
#include "pixmap_loader.h"

VerticalWall::VerticalWall(int x, int y, const QColor& color) : AbstractTile(x, y, color)
{
    pixmap_ = new QPixmap();

    const std::vector<PixmapLoader::PixmapEntry> pixmapEntries = {{pixmap_, ":/arena/vertical_wall.png"}};

    PixmapLoader::loadPixmaps(pixmapEntries);
}
