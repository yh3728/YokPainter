
#include "canvas.h"
#include "figure.h"

void Canvas::addFigure(Figure* f) {
    figures.push_back(f);
}

void Canvas::draw(QPainter* p) {
    for (auto f : figures) f->draw(p);
}

Canvas::~Canvas() {
    for (auto f : figures) delete f;
}
