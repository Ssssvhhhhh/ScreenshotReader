#include "svgframe.h"
#include <qevent.h>
#include <qpainter.h>
#include <qsvgrenderer.h>

SvgFrame::SvgFrame(QWidget *parent) : QFrame(parent) {}

void SvgFrame::setSvgSource(const QString &path)
{
    m_svgSource = path;
    renderer.load(path);
    update();
}

void SvgFrame::setDraggable(bool value)
{
    m_draggable = value;
}

bool SvgFrame::isDraggable()
{
    return m_draggable;
}

void SvgFrame::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    renderer.render(&painter, rect());


}

void SvgFrame::mousePressEvent(QMouseEvent *event)
{
    if (m_draggable && event->button() == Qt::LeftButton)
    {
        dragOffset = event->globalPosition().toPoint() - window()->frameGeometry().topLeft();
        event->accept();
    }
}

void SvgFrame::mouseMoveEvent(QMouseEvent *event)
{
    if (m_draggable && (event->buttons() & Qt::LeftButton))
    {
        window()->move(event->globalPosition().toPoint() - dragOffset);
        event->accept();
    }
}
