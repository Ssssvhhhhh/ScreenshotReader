#ifndef SCREENSELECTOR_H
#define SCREENSELECTOR_H

#include <QWidget>
#include <QRubberBand>
#include <QMouseEvent>
#include <QPainter>


namespace Ui {
class ScreenSelector;
}

class ScreenSelector : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenSelector(QWidget *parent = nullptr);
    ~ScreenSelector();

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent *event) override;
signals:
    void regionSelected(const QRect& geometryWindowData);

private:

    Ui::ScreenSelector *ui;

    QRubberBand* ruberBand;
    QPoint origin;

};

#endif // SCREENSELECTOR_H
