#include "ocrservice.h"


OCRService::OCRService()
{
    imgProc = new ImageProcessor();
    tesEngine = new TesseractEngine();
}

OCRService::~OCRService()
{
    delete tesEngine;
}

QString OCRService::recognize(const QImage &image)
{
    QImage result = image;
    result = imgProc->preprocess(result);
    QString temp = QDir::tempPath() + "/ocr.png";
    result.save(temp);


    return tesEngine->imageToText(temp);
}
