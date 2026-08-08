#ifndef OCRDOCUMENT_H
#define OCRDOCUMENT_H
#include <QString>
#include <QImage>
#include <QFileDialog>

#include <QGuiApplication>
#include <QScreen>

#include "screenselector.h"


class OCRDocument : public QObject
{
    Q_OBJECT

public:
    explicit OCRDocument(QObject *parent = nullptr);

    QString fileName;
    QString filePath;
    QImage image;
    QString recognizedText;


    QScreen* screen;


    void uploadImage();

    public slots:
        void takeAScreenshot(const QRect &rect);

    signals:
        void screenshotReady(const QImage &image);
};

#endif // OCRDOCUMENT_H
