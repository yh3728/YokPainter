#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QColor>
#include "canvas.h"
#include "enums.h"

class CanvasWidget : public QWidget {
    Canvas* canvas;
    Figure* selectedFigure = nullptr;
    QPoint prevMousePos;
    Mode mode = Mode::SELECT;
    FigureType figType = FigureType::RECTANGLE;
    QColor color = Qt::black;
    float selectedFigSize = 1;
public:
    void setMode(Mode _mode) { mode = _mode; }
    void setFigType(FigureType _type) { figType = _type; }
    void setColor(QColor _color) {color = _color;}
    void setSelectedFigSize(float size);
    CanvasWidget(Canvas* c, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // CANVASWIDGET_H
