#pragma once

#include <QtGui/QPixmap>

class PixmapLoader
{
public:
    struct PixmapEntry
    {
        QPixmap* pixmap;
        QString url;
    };

    static void loadPixmaps(const std::vector<PixmapEntry>& pixmapEntries)
    {
        for(const PixmapEntry& pixmapEntry : pixmapEntries)
        {
            if(pixmapEntry.pixmap)
            {
                if(!pixmapEntry.pixmap->load(pixmapEntry.url))
                {
                    throw std::runtime_error("Error, cannot load pixmap from URL: " + pixmapEntry.url.toStdString());
                }
            }
            else
            {
                throw std::runtime_error("Error, pixmap pointer is null for URL: " + pixmapEntry.url.toStdString());
            }
        }
    }
};
