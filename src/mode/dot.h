#ifndef DOT_H
#define DOT_H

namespace Shape {

class Dot : public Drawable {
public:
    Dot(Point p) : Drawable(std::vector<Point>{p});
    Dot(double x, double y) : Drawable(std::vector<Point>{Point(x, y)}) {}
};

}  // namespace Shape

#endif  // DOT_H