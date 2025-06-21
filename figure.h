#ifndef FIGURE_H
#define FIGURE_H

#include <QPoint>
#include <QPainter>
#include <QColor>
#include "figure.h"
#include "affine_transform.h"

class Figure
{

public:
    virtual ~Figure() {}
    Figure(QPoint first, QPoint second, QColor color);
    virtual void draw(QPainter* p) = 0;
    virtual void move(const AffineTransform &trans) = 0;
    virtual void rotate(const AffineTransform &trans) = 0;
    virtual void scale(const AffineTransform &trans) = 0;
    virtual bool isPointInside(const QPoint &point) = 0;
    bool isSelected() const { return selected; }
    void setSelected(bool s) { selected = s; }
    QPointF center;
protected:
    QPoint bBox[2];
    bool selected = false;
    QColor color;
    QPen pen;
    QPen redPen{Qt::red, 2, Qt::DashLine};
    double size = 1;
};

class CircleFigure: public Figure{
private:
    int a;
    int oldA;
public:
    CircleFigure(const QPoint first, const QPoint second, const QColor color);
    void draw(QPainter *p) override;
    double angle = 0.0;
    virtual void move(const AffineTransform &trans) override;
    virtual void rotate(const AffineTransform &trans) override;
    virtual void scale(const AffineTransform &trans) override;
    virtual bool isPointInside(const QPoint &point) override;
};

class RectFigure: public Figure{
private:
    QPointF A, B, C, D;
    QPointF oldA, oldB, oldC, oldD;
public:
    RectFigure(const QPoint first, const QPoint second, const QColor color);
    void draw(QPainter* p) override;
    virtual void move(const AffineTransform &trans) override;
    virtual void rotate(const AffineTransform &trans) override;
    virtual void scale(const AffineTransform &trans) override;
    virtual bool isPointInside(const QPoint &point) override;
};

class TriangleFigure: public Figure{
private:
    QPointF A, B, C;
    QPointF oldA, oldB, oldC;
public:
    TriangleFigure(const QPoint first, const QPoint second, const QColor color);
    void draw(QPainter* p) override;
    virtual void move(const AffineTransform &trans) override;
    virtual void rotate(const AffineTransform &trans) override;
    virtual void scale(const AffineTransform &trans) override;
    virtual bool isPointInside(const QPoint &point) override;
};

#endif // FIGURE_H
