#pragma once

#include <QtGui/QPixmap>

class PixmapLoader
{
public:
    //    static bool loadPixmap(QPixmap* pixmap, const QString& imageUrl)
    //    {
    //        if(pixmap)
    //        {
    //            if(!pixmap->load(imageUrl))
    //            {
    //                throw std::runtime_error("Error, cannot load pixmap: " + imageUrl.toStdString());
    //            }
    //        }
    //        else
    //        {
    //            throw std::runtime_error("Error, pixmap is null: " + imageUrl.toStdString());
    //        }
    //    }

    static void loadPixmap(const std::pair<QPixmap*, QString>& pixmapToImageUrlPair)
    {
        QPixmap* pixmap = pixmapToImageUrlPair.first;
        QString imageUrl = pixmapToImageUrlPair.second;

        if(pixmap)
        {
            if(!pixmap->load(imageUrl))
            {
                throw std::runtime_error("Error, cannot load pixmap: " + imageUrl.toStdString());
            }
        }
        else
        {
            throw std::runtime_error("Error, pixmap is null: " + imageUrl.toStdString());
        }
    }
};
