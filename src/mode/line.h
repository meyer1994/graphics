#ifndef LINE_H
#define LINE_H

#include "drawable.h"

class Line : public Drawable {
public:
    Line(Point a, Point b) : Drawable(std::vector<Point>{a, b}) {}

};

#endif  // LINE_H