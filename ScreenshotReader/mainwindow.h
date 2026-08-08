#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "OCRDocument.h"
#include "screenselector.h"
#include "ocrservice.h"
#include "ocrworker.h"


#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_uploadBtn_clicked();
    void on_takeScreenshotBtn_clicked();
    void showScreenshot(const QImage &image);
    void showRecognizedText(const QString& text);

signals:
    void startOCR(const QImage& image);

private:
    Ui::MainWindow *ui;
    OCRDocument* ocrdDoc;
    ScreenSelector* selector;
    OCRService *ocrSer;
    OCRWorker* worker;
    QThread *thread;
};
#endif // MAINWINDOW_H
