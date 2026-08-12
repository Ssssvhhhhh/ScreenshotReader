#ifndef SVGFRAME_H
#define SVGFRAME_H

#include <QObject>
#include <QWidget>
#include <qframe.h>
#include <qpainter.h>
#include <qsvgrenderer.h>

class SvgFrame : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(QString svgSource READ svgSource WRITE setSvgSource)
    Q_PROPERTY(bool draggable READ isDraggable WRITE setDraggable)

public:
    explicit SvgFrame(QWidget* parent = nullptr);
    QString svgSource() const { return m_svgSource; }
    void setSvgSource(const QString &path);
    void setDraggable(bool value);
    bool isDraggable();

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    QString m_svgSource;
    QSvgRenderer renderer;
    bool m_draggable = false;
    QPoint dragOffset;
};

#endif // SVGFRAME_H
