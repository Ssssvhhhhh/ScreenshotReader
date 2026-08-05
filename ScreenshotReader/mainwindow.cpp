#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)


{
    ui->setupUi(this);

    selector = new ScreenSelector(nullptr);



    ocrdDoc  = new OCRDocument(this);

    connect(selector,&ScreenSelector::regionSelected,ocrdDoc,&OCRDocument::takeAScreenshot);

    connect(ocrdDoc,&OCRDocument::screenshotReady,this,&MainWindow::showScreenshot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_uploadBtn_clicked()
{
    ocrdDoc->uploadImage();

}


void MainWindow::on_takeScreenshotBtn_clicked()
{
    hide();

    selector->show();
    selector->raise();
    selector->activateWindow();
    selector->showFullScreen();
}

void MainWindow::showScreenshot(const QPixmap &pixmap)
{
    show();
    ui->label->setPixmap(pixmap);
}

