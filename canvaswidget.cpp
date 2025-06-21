#include "canvaswidget.h"
#include "affine_transform.h"
#include "enums.h"
#include <iostream>
#include <QMouseEvent>

void CanvasWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    canvas->draw(&painter);
}

CanvasWidget::CanvasWidget(Canvas* c, QWidget* parent) : QWidget(parent), canvas(c) {
    setMinimumSize(600, 600);
}

void CanvasWidget::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && mode==Mode::SELECT){
        if (selectedFigure == nullptr){
            for (auto figure: canvas->figures){
                if (figure->isPointInside(event->position().toPoint())){
                    figure->setSelected(true);
                    selectedFigure = figure;
                    break;
                }
            }
        }
        else
        {
            selectedFigure->setSelected(false);
            selectedFigure = nullptr;
        }
        update();
    }
    if (event->button() == Qt::RightButton) {
        prevMousePos = event->pos();
    }
    if (event->button() == Qt::LeftButton && mode == Mode::PAINT){
        prevMousePos = event->pos();
    }
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event){
    if (!(event->buttons() & Qt::RightButton) || selectedFigure == nullptr)
        return;
    QPoint currentMousePos = event->pos();
    QPoint delta = currentMousePos - prevMousePos;
    if (selectedFigure->isPointInside((event->position().toPoint()))){
        selectedFigure->move(AffineTransform::translation(delta));
        update();
    }
    else {

        QPointF v1 = prevMousePos - selectedFigure->center;
        QPointF v2 = currentMousePos - selectedFigure->center;

        float angle = std::atan2(v2.y(), v2.x()) - std::atan2(v1.y(), v1.x());
        selectedFigure->rotate(AffineTransform::rotate(angle));
        update();

    }
    prevMousePos = currentMousePos;

}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && mode == Mode::PAINT){
        QPoint currentMousePos = event->pos();
        switch(figType){
        case FigureType::RECTANGLE:
            canvas->addFigure(new RectFigure(prevMousePos, currentMousePos, color));
            update();
            break;
        case FigureType::CIRCLE:
            canvas->addFigure(new CircleFigure(prevMousePos, currentMousePos, color));
            update();
            break;
        case FigureType::TRIANGLE:
            canvas->addFigure(new TriangleFigure(prevMousePos, currentMousePos, color));
            update();
            break;
        }
    }
}

void CanvasWidget::setSelectedFigSize(float size){
    if (selectedFigure == nullptr)
        return;
    selectedFigure->scale(AffineTransform::scale(size));
    update();
}


