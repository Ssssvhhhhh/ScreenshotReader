#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)


{
    ui->setupUi(this);


    //Visual


    setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    //setWindowOpacity(0.8);



    selector = new ScreenSelector(nullptr);
    ocrSer = new OCRService();
    ocrdDoc  = new OCRDocument(this);

    connect(selector,&ScreenSelector::regionSelected,ocrdDoc,&OCRDocument::takeAScreenshot);
    connect(ocrdDoc,&OCRDocument::screenshotReady,this,&MainWindow::showScreenshot);

    movie = new QMovie("assets/load.gif");
    movie->setScaledSize(QSize(150, 150));
    ui->loadingLabel->setMovie(movie);
    ui->loadingLabel->setVisible(false);
    //ui->dial->setVisible(false);
    //connect(worker, &OCRWorker::finished, this, &MainWindow::showRecognizedText);
}

MainWindow::~MainWindow()
{
    delete ui;
    //delete tesEng;
}



void MainWindow::hideWindow()
{
    hide();
}

void MainWindow::exit()
{
    close();
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


    //connect(worker,&OCRWorker::progress, this, &MainWindow::showLoadingAnimation);






    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
    ui->textBrowserFrame->clear();
    showLoadingAnimation();
    emit startOCR(image);


    thread->start();

    show();

}

void MainWindow::showRecognizedText(const QString &text)
{
    ui->textBrowserFrame->setText(text);
    showLoadingAnimation();
}
//Fix later
void MainWindow::showLoadingAnimation()
{
    if(ui->loadingLabel->isVisible())
    {
        ui->loadingLabel->setVisible(false);
        movie->stop();
    }
    else
    {
       ui->loadingLabel->setVisible(true);
        movie->start();

    }


}


void MainWindow::on_hideBtn_clicked()
{
    showMinimized();
}


void MainWindow::on_exitBtn_clicked()
{
    exit();
}

