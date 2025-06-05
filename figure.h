#ifndef FIGURE_H
#define FIGURE_H

#include <QPoint>
#include <QPainter>
#include "figure.h"

class Figure
{
public:
    virtual ~Figure() {}
    virtual void draw(QPainter* p) = 0;
};

class EllipseFigure: public Figure{
private:
    QPoint center;
    int a, b;
public:
    EllipseFigure(QPoint first, QPoint second);
    void draw(QPainter *p) override;
};

class RectFigure: public Figure{
private:
    QPoint A, B, C, D;
public:
    RectFigure(QPoint first, QPoint second);
    void draw(QPainter* p) override;
};

#endif // FIGURE_H
