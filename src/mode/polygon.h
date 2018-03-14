#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"

class Polygon : public Shape {
public:
    Polygon() : Shape() {}

    explicit Polygon(std::vector<Point> points) : Shape(points) {}
};

#endif  // POLYGON_H
