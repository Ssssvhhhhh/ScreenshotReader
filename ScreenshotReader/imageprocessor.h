#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QImage>

class ImageProcessor
{
public:
    ImageProcessor();
    QImage preprocess(const QImage& image);


private:
    //QImage scale(const QImage& image, int factor);
    QImage toGray(const QImage& image);
    QImage increaseContrast (const QImage& image);
    QImage threshold(const QImage& image, int value);
    QImage invert(const QImage& image);

};

#endif // IMAGEPROCESSOR_H
