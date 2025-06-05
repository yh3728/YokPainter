#include "figure.h"

EllipseFigure::EllipseFigure(QPoint first, QPoint second) {
    int left = std::min(first.x(), second.x());
    int right = std::max(first.x(), second.x());
    int top = std::min(first.y(), second.y());
    int bottom = std::max(first.y(), second.y());

    center = QPoint((left + right) / 2, (top + bottom) / 2);
    a = (right - left) / 2;
    b = (bottom - top) / 2;
}


void EllipseFigure::draw(QPainter *p){

    p->drawEllipse(center, a, b);
}

RectFigure::RectFigure(QPoint first, QPoint second){
    int minx = std::min(first.x(), second.x());
    int maxx = std::max(first.x(), second.x());
    int miny = std::min(first.y(), second.y());
    int maxy = std::max(first.y(), second.y());
    A = QPoint(minx, miny);
    B = QPoint(minx, maxy);
    C = QPoint(maxx, maxy);
    D = QPoint(maxx, miny);
}

void RectFigure::draw(QPainter* p){
    p->drawRect(QRect(B, D));
}
