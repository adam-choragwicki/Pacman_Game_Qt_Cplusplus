#include "corner_wall_nw.h"
#include "pixmap_loader.h"

CornerWallNW::CornerWallNW(int x, int y, const QColor& color) : AbstractTile(x, y, color)
{
    pixmap_ = new QPixmap();

    const std::vector<PixmapLoader::PixmapEntry> pixmapEntries = {{pixmap_, ":/arena/corner_wall_NW.png"}};

    PixmapLoader::loadPixmaps(pixmapEntries);
}
