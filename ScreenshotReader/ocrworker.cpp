#include "ocrworker.h"
#include <qthread.h>



OCRWorker::OCRWorker(QObject *parent) : QObject(parent)
{
    ocrSer = new OCRService();
}

void OCRWorker::doWork(const QImage &image)
{
    qDebug() << "Работа началась в потоке:" << QThread::currentThreadId();


    qDebug() << "===== OCR START =====";
    qDebug() << "Null:" << image.isNull();
    qDebug() << "Size:" << image.size();
    qDebug() << "Format:" << image.format();



    emit finished(ocrSer->recognize(image));
    qDebug() << "Работа end в потоке:" << QThread::currentThreadId();

}
