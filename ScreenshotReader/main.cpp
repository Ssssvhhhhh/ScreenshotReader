#include "mainwindow.h"

#include <QApplication>


#include <tesseract/baseapi.h>

int main(int argc, char *argv[])
{
    /*
    tesseract::TessBaseAPI api;

    if (api.Init("tessdata", "rus")) {
        qDebug() << "Ошибка";
    }
    */



    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
