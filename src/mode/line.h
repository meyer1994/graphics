#ifndef LINE_H
#define LINE_H

#include "drawable.h"

namespace Shape {

class Line : public Drawable {
public:
    Line(Point a, Point b) : Drawable(std::vector<Point>{a, b}) {}

};

}  // namespace Shape

#endif  // LINE_H