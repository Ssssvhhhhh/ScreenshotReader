#ifndef OCRWORKER_H
#define OCRWORKER_H

#include "ocrservice.h"
#include <QThread>

class OCRWorker : public QObject
{
    Q_OBJECT
public slots:
    void doWork(const QImage &image);

public:
    explicit OCRWorker(QObject *parent = nullptr);
    OCRWorker();

signals:
    void finished(const QString& text);
    //void progress(const int& percent);

private:
    OCRService* ocrSer;

};

#endif // OCRWORKER_H
