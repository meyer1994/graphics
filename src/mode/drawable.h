#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <vector>
#include "point.h"

class Drawable {
public:
    Drawable() : points() {}
    explicit Drawable(std::vector<Point> points_in) : points(points_in) {}

    std::vector<Point> points;
};

#endif  // DRAWABLE_H