#ifndef OCRSERVICE_H
#define OCRSERVICE_H
#include "imageprocessor.h"
#include "tesseractengine.h"


class OCRService
{
public:
    OCRService();
    ~OCRService();
    QString recognize(const QImage &image);


private:
    ImageProcessor* imgProc;
    TesseractEngine* tesEngine;

    //QString recognizedText;
};

#endif // OCRSERVICE_H
