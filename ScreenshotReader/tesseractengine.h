#ifndef TESSERACTENGINE_H
#define TESSERACTENGINE_H
#include <QImage>
#include <QDebug>
#include <QDir>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

class TesseractEngine
{
public:
    TesseractEngine();
    ~TesseractEngine();
    bool initialized;
    QString imageToText(const QString &temdDir);
    tesseract::TessBaseAPI api;

};

#endif // TESSERACTENGINE_H
