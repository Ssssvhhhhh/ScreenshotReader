#include "ocrdocument.h"
#include <qapplication.h>

OCRDocument::OCRDocument(QObject *parent)
    : QObject(parent)
{
    screen = QGuiApplication::primaryScreen();
}

void OCRDocument::uploadImage()
{
    filePath = QFileDialog::getOpenFileName(nullptr, "Select a file", "", "Images (*.png *.jpg)");

    if(filePath.isEmpty()) qDebug() << "FilePath is empty";

    QPixmap image(filePath);

    emit screenshotReady(image);

}

void OCRDocument::takeAScreenshot(const QRect &rect)
{
    QScreen *screen = QGuiApplication::primaryScreen();

    QPixmap image = screen->grabWindow(
        0,
        rect.x(),
        rect.y(),
        rect.width(),
        rect.height());

    emit screenshotReady(image);
}
