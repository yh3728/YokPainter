#include "affine_transform.h"
#include <QPoint>

QPointF AffineTransform::apply(const QPointF& p) const{
    double x = A[0][0] * p.x() + A[0][1] * p.y() + t[0];
    double y = A[1][0] * p.x() + A[1][1] * p.y() + t[1];
    return QPointF(x, y);
}

AffineTransform::AffineTransform(double a11, double a12, double a21, double a22, double tx, double ty) {
    A[0][0] = a11; A[0][1] = a12;
    A[1][0] = a21; A[1][1] = a22;
    t[0] = tx;
    t[1] = ty;
}

AffineTransform AffineTransform::translation(QPointF point){
    return AffineTransform(1, 0, 0, 1, point.x(), point.y());
}

AffineTransform AffineTransform::rotate(double angle){
    return AffineTransform(cos(angle), -1 * sin(angle), sin(angle), cos(angle), 0, 0);
}

AffineTransform AffineTransform::scale(double sizeCoeff){
    return AffineTransform(sizeCoeff, 0, 0, sizeCoeff, 0, 0);
}
