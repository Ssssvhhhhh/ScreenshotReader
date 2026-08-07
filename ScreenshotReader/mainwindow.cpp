#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)


{
    ui->setupUi(this);

    selector = new ScreenSelector(nullptr);


    ocrSer = new OCRService();
    ocrdDoc  = new OCRDocument(this);

    connect(selector,&ScreenSelector::regionSelected,ocrdDoc,&OCRDocument::takeAScreenshot);

    connect(ocrdDoc,&OCRDocument::screenshotReady,this,&MainWindow::showScreenshot);
}

MainWindow::~MainWindow()
{
    delete ui;
    //delete tesEng;

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

    QImage image = pixmap.toImage();
    ocrSer->recognize(image);

    ui->textBrowser->setText(ocrSer->recognize(image));
}

