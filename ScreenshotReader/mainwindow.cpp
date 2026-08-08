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




    //connect(worker, &OCRWorker::finished, this, &MainWindow::showRecognizedText);
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

void MainWindow::showScreenshot(const QImage &image)
{

    worker = new OCRWorker(nullptr);
    thread = new QThread();
    worker->moveToThread(thread);



    connect(this, &MainWindow::startOCR,worker, &OCRWorker::doWork);
    connect(worker, &OCRWorker::finished, this, &MainWindow::showRecognizedText);
    connect(worker, &OCRWorker::finished,thread, &QThread::quit);
    connect(worker, &OCRWorker::finished,worker, &QObject::deleteLater);
    connect(thread, &QThread::finished,thread, &QObject::deleteLater);








    ui->label->setPixmap(QPixmap::fromImage(image));
    emit startOCR(image);
    thread->start();

    show();

}

void MainWindow::showRecognizedText(const QString &text)
{
    ui->textBrowser->setText(text);

}

