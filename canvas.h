#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include "figure.h"
#include <QPainter>

class Canvas {
public:
    std::vector<Figure*> figures;

    void addFigure(Figure* f);

    void draw(QPainter* p);

    ~Canvas();
};

#endif // CANVAS_H
