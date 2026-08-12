#include "ocrworker.h"
#include <qthread.h>



OCRWorker::OCRWorker(QObject *parent) : QObject(parent)
{
    ocrSer = new OCRService();
}

void OCRWorker::doWork(const QImage &image)
{

    QString result = ocrSer->recognize(image);


    //emit progress(101);
    emit finished(result);

}
