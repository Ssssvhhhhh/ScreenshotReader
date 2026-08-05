#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "OCRDocument.h"
#include "screenselector.h"

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
    void showScreenshot(const QPixmap &pixmap);

private:
    Ui::MainWindow *ui;
    OCRDocument* ocrdDoc;
    ScreenSelector* selector;
};
#endif // MAINWINDOW_H
