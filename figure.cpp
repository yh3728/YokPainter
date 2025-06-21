#include "figure.h"
#include <QPoint>
#include <QPainter>
#include <iostream>
#include "affine_transform.h"

Figure::Figure(const QPoint first, const QPoint second, QColor color){
    int left = std::min(first.x(), second.x());
    int right = std::max(first.x(), second.x());
    int top = std::min(first.y(), second.y());
    int bottom = std::max(first.y(), second.y());
    bBox[0] = QPoint(left, top);
    bBox[1] = QPoint(right, bottom);
    pen.setColor(color);
}

CircleFigure::CircleFigure(const QPoint first, const QPoint second, const QColor color)
    : Figure(first, second, color)
    {
    center = QPoint((bBox[0].x() + bBox[1].x()) / 2, (bBox[0].y() + bBox[1].y()) / 2);
    int a1 = (bBox[1].x() - bBox[0].x()) / 2;
    int b = (bBox[1].y() - bBox[0].y()) / 2;
    a = std::min(a1, b);
    oldA = a;
}

void CircleFigure::draw(QPainter *p){
    p->setPen(pen);
    p->drawEllipse(center, a, a);
    if (selected) {
        p->setPen(redPen);
        p->drawEllipse(center, a, a);
        p->setPen(pen);
    }
}

void CircleFigure::move(const AffineTransform &trans){
    center = trans.apply(center);
}

void CircleFigure::rotate(const AffineTransform &trans){

}

void CircleFigure::scale(const AffineTransform &trans){
    QPointF pointA = QPoint(oldA, oldA);
    a = trans.apply(pointA).x();
}

bool CircleFigure::isPointInside(const QPoint &point){
    double dx = point.x() - center.x();
    double dy = point.y() - center.y();
    return (dx * dx) + (dy * dy) <= a * a;

}

RectFigure::RectFigure(const QPoint first, const QPoint second, const QColor color)
    : Figure(first, second, color)
{
    oldA = A = QPointF(bBox[0].x(), bBox[0].y());
    oldB = B = QPointF(bBox[0].x(), bBox[1].y());
    oldC = C = QPointF(bBox[1].x(), bBox[1].y());
    oldD = D = QPointF(bBox[1].x(), bBox[0].y());
    center = QPointF((A.x() + C.x()) / 2, (A.y() + C.y()) / 2);
}

void RectFigure::draw(QPainter* p){
    p->setPen(pen);
    QPolygonF rect;
    rect << A << B << C << D;
    p->drawPolygon(rect);
    if (selected) {
        p->setPen(redPen);
        p->drawPolygon(rect);
        p->setPen(pen);
    }
}

void RectFigure::move(const AffineTransform &trans){
    oldA = A = trans.apply(A);
    oldB = B = trans.apply(B);
    oldC = C = trans.apply(C);
    oldD = D = trans.apply(D);
    center = QPointF((A.x() + C.x()) / 2, (A.y() + C.y()) / 2);
}

void RectFigure::rotate(const AffineTransform &trans){

    QPointF A_rel = A - center;
    QPointF B_rel = B - center;
    QPointF C_rel = C - center;
    QPointF D_rel = D - center;

    A_rel = trans.apply(A_rel);
    B_rel = trans.apply(B_rel);
    C_rel = trans.apply(C_rel);
    D_rel = trans.apply(D_rel);

    oldA = A = A_rel + center;
    oldB = B = B_rel + center;
    oldC = C = C_rel + center;
    oldD = D = D_rel + center;

}

void RectFigure::scale(const AffineTransform &trans){

    QPointF A_rel = oldA - center;
    QPointF B_rel = oldB - center;
    QPointF C_rel = oldC - center;
    QPointF D_rel = oldD - center;

    A_rel = trans.apply(A_rel);
    B_rel = trans.apply(B_rel);
    C_rel = trans.apply(C_rel);
    D_rel = trans.apply(D_rel);

    A = A_rel + center;
    B = B_rel + center;
    C = C_rel + center;
    D = D_rel + center;
}


bool RectFigure::isPointInside(const QPoint &point){
    QPolygonF polygon;
    polygon << A << B << C << D;
    return polygon.containsPoint(point, Qt::OddEvenFill);
}


TriangleFigure::TriangleFigure(const QPoint first, const QPoint second, const QColor color)
    : Figure(first, second, color)
{
    oldA = A = QPointF(bBox[0].x(), bBox[1].y());
    oldB = B = QPointF((bBox[1].x() + bBox[0].x())/2, bBox[0].y());
    oldC = C = QPointF(bBox[1].x(), bBox[1].y());
    center = QPointF((A.x() + B.x() + C.x()) / 3.0, (A.y() + B.y() + C.y()) / 3.0);

}

void TriangleFigure::draw(QPainter* p){
    p->setPen(pen);
    QPolygonF triangle;
    triangle << A << B << C;
    p->drawPolygon(triangle);
    if (selected) {
        p->setPen(redPen);
        p->drawPolygon(triangle);
        p->setPen(pen);
    }
}

void TriangleFigure::move(const AffineTransform &trans){
    oldA = A = trans.apply(A);
    oldB = B = trans.apply(B);
    oldC = C = trans.apply(C);
    center = QPointF((A.x() + B.x() + C.x()) / 3.0, (A.y() + B.y() + C.y()) / 3.0);
}

void TriangleFigure::rotate(const AffineTransform &trans){

    QPointF A_rel = A - center;
    QPointF B_rel = B - center;
    QPointF C_rel = C - center;

    A_rel = trans.apply(A_rel);
    B_rel = trans.apply(B_rel);
    C_rel = trans.apply(C_rel);

    oldA = A = A_rel + center;
    oldB = B = B_rel + center;
    oldC = C = C_rel + center;

}

void TriangleFigure::scale(const AffineTransform &trans){

    QPointF A_rel = oldA - center;
    QPointF B_rel = oldB - center;
    QPointF C_rel = oldC - center;

    A_rel = trans.apply(A_rel);
    B_rel = trans.apply(B_rel);
    C_rel = trans.apply(C_rel);

    A = A_rel + center;
    B = B_rel + center;
    C = C_rel + center;
}


bool TriangleFigure::isPointInside(const QPoint &point){
    QPolygonF polygon;
    polygon << A << B << C;
    return polygon.containsPoint(point, Qt::OddEvenFill);
}

