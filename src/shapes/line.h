#ifndef LINE_H
#define LINE_H

#include "drawable.h"

namespace Shape {

class Line : public Drawable {
public:
    Line(
        const Coordinate& a,
        const Coordinate& b,
        const std::string name = "line")
    : Drawable(std::vector<Coordinate> {a, b}, name) {}

    ~Line() {}
};

}  // namespace Shape

#endif  // LINE_H