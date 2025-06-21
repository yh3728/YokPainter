#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H
#include <QPoint>

struct AffineTransform {
    double A[2][2];  // линейное преобразование
    double t[2];     // перенос

    QPointF apply(const QPointF& p) const;
    static AffineTransform translation(QPointF point); //перенос
    static AffineTransform rotate(double angle); //поворот
    static AffineTransform scale(double sizeCoeff); //масштабирование
    AffineTransform(double a11, double a12, double a21, double a22, double tx, double ty);
};

#endif // AFFINE_TRANSFORM_H
