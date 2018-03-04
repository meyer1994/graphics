#ifndef LINE_H
#define LINE_H

#include "drawable.h"

class Line : public Drawable {
public:
    Line(const std::string name, const Point& a, const Point& b) :
        Drawable(name, std::vector<Point> {a, b}) {}

	~Line() {}
};

#endif  // LINE_H