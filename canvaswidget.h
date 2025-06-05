#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QPainter>
#include "canvas.h"

class CanvasWidget : public QWidget {
    Canvas* canvas;

public:
    CanvasWidget(Canvas* c, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent*) override;
};


#endif // CANVASWIDGET_H
