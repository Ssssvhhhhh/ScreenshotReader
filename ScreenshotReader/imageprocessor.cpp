#include "imageprocessor.h"

ImageProcessor::ImageProcessor() {}

QImage ImageProcessor::preprocess(const QImage &image)
{
    QImage result = toGray(image);
    result = increaseContrast(result);
    //result = threshold(result,170);
    result = invert(result);

    return result;
}

QImage ImageProcessor::toGray(const QImage &image)
{
    QImage gray = image.convertToFormat(QImage::Format_Grayscale8);
    gray = gray.scaled(
        gray.width() * 2,
        gray.height() * 2,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        );

    return gray;
}

QImage ImageProcessor::increaseContrast(const QImage &image)
{
    QImage result = image.convertToFormat(QImage::Format_ARGB32);

    for (int i = 0; i < image.height(); ++i)
    {
        QRgb *line = reinterpret_cast<QRgb*>(result.scanLine(i));

        for (int j = 0; j < image.width(); ++j)
        {
            QRgb pixel = line[j];

            int r = qRed(pixel);
            int g = qGreen(pixel);
            int b = qBlue(pixel);
            int a = qAlpha(pixel);

            r = qBound(0, static_cast<int>((r - 128) * 1.5 + 128), 255);
            g = qBound(0, static_cast<int>((g - 128) * 1.5 + 128), 255);
            b = qBound(0, static_cast<int>((b - 128) * 1.5 + 128), 255);

            line[j] = qRgba(r, g, b, a);

        }
    }

    return result;

}

QImage ImageProcessor::threshold(const QImage &image, int value)
{
    QImage result = image.convertToFormat(QImage::Format_Grayscale8);

    for (int y = 0; y < result.height(); ++y)
    {
        uchar *line = result.scanLine(y);

        for (int x = 0; x < result.width(); ++x)
        {
            line[x] = (line[x] > value) ? 255 : 0;
        }
    }

    return result;
}

QImage ImageProcessor::invert(const QImage &image)
{
    QImage result = image;

    result.invertPixels();

    return result;
}
