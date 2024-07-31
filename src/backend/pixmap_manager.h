#pragma once

#include <QtGui/QPixmap>

class PixmapManager
{
public:
    static QPixmap scalePixmap(QPixmap* pixmap, const QRectF targetRect)
    {
        return pixmap->scaled(static_cast<int>(targetRect.width()), static_cast<int>(targetRect.height()), Qt::AspectRatioMode::IgnoreAspectRatio, Qt::TransformationMode::SmoothTransformation);
    }

    static QPixmap rotatePixmap90DegreesClockwise(QPixmap* pixmap)
    {
        QTransform rotate90DegreesClockwise;
        rotate90DegreesClockwise.rotate(+90);
        return pixmap->transformed(rotate90DegreesClockwise, Qt::TransformationMode::SmoothTransformation);
    }

    static QPixmap rotatePixmap90DegreesCounterclockwise(QPixmap* pixmap)
    {
        QTransform rotate90DegreesCounterclockwise;
        rotate90DegreesCounterclockwise.rotate(-90);
        return pixmap->transformed(rotate90DegreesCounterclockwise, Qt::TransformationMode::SmoothTransformation);
    }

    static QPixmap mirrorPixmapHorizontally(QPixmap* pixmap)
    {
        QTransform horizontalMirrorTransformation;
        horizontalMirrorTransformation.scale(-1, +1);
        return pixmap->transformed(horizontalMirrorTransformation, Qt::TransformationMode::SmoothTransformation);
    }
};
