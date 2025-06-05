#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include "figure.h"
#include <QPainter>

class Canvas {
    std::vector<Figure*> figures;

public:
    void addFigure(Figure* f);

    void draw(QPainter* p);

    ~Canvas();
};

#endif // CANVAS_H
