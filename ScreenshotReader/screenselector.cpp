#include "screenselector.h"
#include "ui_screenselector.h"

ScreenSelector::ScreenSelector(QWidget *parent)
    : QWidget(nullptr),
    ui(new Ui::ScreenSelector)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint |
                   Qt::WindowStaysOnTopHint |
                   Qt::Tool);

    setAttribute(Qt::WA_TranslucentBackground);

    setGeometry(QGuiApplication::primaryScreen()->geometry());

    ruberBand = new QRubberBand(QRubberBand::Rectangle, this);
}

ScreenSelector::~ScreenSelector()
{
    delete ui;
}

void ScreenSelector::mousePressEvent(QMouseEvent *event)
{
    origin = event->pos();
    ruberBand->setGeometry(QRect(origin, QSize()));
    ruberBand->show();
    QWidget::mousePressEvent(event);
}

void ScreenSelector::mouseMoveEvent(QMouseEvent *event)
{
    if(ruberBand->isVisible()) ruberBand->setGeometry((QRect(origin, event->pos()).normalized()));
    QWidget::mouseMoveEvent(event);
}

void ScreenSelector::mouseReleaseEvent(QMouseEvent *event)
{
    ruberBand->hide();

    QRect rect = ruberBand->geometry();

    QPoint globalPos = mapToGlobal(rect.topLeft());

    QRect globalRect(globalPos, rect.size());

    close();

    emit regionSelected(globalRect);
}

void ScreenSelector::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.fillRect( rect(),QColor(0,0,0,80));
}
