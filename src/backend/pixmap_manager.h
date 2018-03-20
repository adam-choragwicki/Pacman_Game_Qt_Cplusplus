#pragma once

#include <QtGui/QPixmap>

class PixmapManager
{
public:
    static QPixmap scalePixmap(QPixmap* pixmap, const QRectF targetRect)
    {
        QPixmap transformedPixmap = pixmap->scaled(static_cast<int>(targetRect.width()), static_cast<int>(targetRect.height()), Qt::AspectRatioMode::IgnoreAspectRatio, Qt::TransformationMode::SmoothTransformation);

        if(!transformedPixmap.isNull())
        {
            return std::move(transformedPixmap);
        }
        else
        {
            throw std::runtime_error("Error during scaling pixmap. Pixmap is null");
        }
    }

    static QPixmap rotatePixmap90DegreesClockwise(QPixmap* pixmap)
    {
        QTransform rotate90DegreesClockwise;
        rotate90DegreesClockwise.rotate(+90);

        QPixmap transformedPixmap = pixmap->transformed(rotate90DegreesClockwise, Qt::TransformationMode::SmoothTransformation);

        if(!transformedPixmap.isNull())
        {
            return std::move(transformedPixmap);
        }
        else
        {
            throw std::runtime_error("Error during rotating pixmap 90 degrees clockwise. Pixmap is null");
        }
    }

    static QPixmap rotatePixmap90DegreesCounterclockwise(QPixmap* pixmap)
    {
        QTransform rotate90DegreesCounterclockwise;
        rotate90DegreesCounterclockwise.rotate(-90);

        QPixmap transformedPixmap = pixmap->transformed(rotate90DegreesCounterclockwise, Qt::TransformationMode::SmoothTransformation);

        if(!transformedPixmap.isNull())
        {
            return std::move(transformedPixmap);
        }
        else
        {
            throw std::runtime_error("Error during rotating pixmap 90 degrees counterclockwise. Pixmap is null");
        }
    }

    static QPixmap mirrorPixmapHorizontally(QPixmap* pixmap)
    {
        QTransform horizontalMirrorTransformation;
        horizontalMirrorTransformation.scale(-1, +1);

        QPixmap transformedPixmap = pixmap->transformed(horizontalMirrorTransformation, Qt::TransformationMode::SmoothTransformation);

        if(!transformedPixmap.isNull())
        {
            return std::move(transformedPixmap);
        }
        else
        {
            throw std::runtime_error("Error during mirroring pixmap horizontally. Pixmap is null");
        }
    }
};
