#ifndef DOT_H
#define DOT_H

#include <string>
#include <vector>

#include "line.h"
#include "point.h"

class Dot : public Line {
public:
    Dot() : Line(name = "dot") {}

    explicit Dot(std::string name) : Line(name) {}

    Dot(double x, double y, double z = 0, std::string name = "dot")
    : Line(Point(x, y, z), Point(x, y, z), name) {}

    Dot(Point point, std::string name = "dot") : Line(point, point, name) {}

    virtual ~Dot() {}

    virtual const std::string to_string() const override {
        std::string str = "Dot(";
        str += a.to_string();
        str += ")";
        return str;
    }

    virtual const Type2D type() const override {
        return Type2D::Dot;
    }
};

#endif  // DOT_H
