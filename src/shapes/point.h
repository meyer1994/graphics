#ifndef POINT_H
#define POINT_H

#include "drawable.h"

namespace Shape {

class Point : public Drawable {
public:
    Point(
        const double x, 
        const double y,
        const std::string name = "point")
    : Drawable(std::vector<Coordinate> { Coordinate {x, y} }, name) {}
    
    ~Point() {}
};

}  // namespace Shape

#endif  // POINT_H