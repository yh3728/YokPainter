#include "canvaswidget.h"

void CanvasWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    canvas->draw(&painter);
}

CanvasWidget::CanvasWidget(Canvas* c, QWidget* parent) : QWidget(parent), canvas(c) {
    setMinimumSize(600, 600);
}
