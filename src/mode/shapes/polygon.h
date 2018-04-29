#ifndef POLYGON_H
#define POLYGON_H

#include <string>
#include <vector>
#include <initializer_list>

#include "point.h"
#include "shape.h"

class Polygon : public Shape {
public:
    Polygon() : Shape("polygon") {}

    Polygon(std::string name) : Shape(name) {}

    Polygon(std::initializer_list<Point> d) : Shape(d, "polygon") {}

    Polygon(std::vector<Point> points, std::string name = "polygon")
    : Shape(points, name) {}

    virtual ~Polygon() {}

    virtual const std::string to_string() const override {
        if (real.empty()) {
            return "Polygon()";
        }

        std::string str = "Polygon(";
        for (int i = 0; i < real.size() - 1; i++) {
            const Point& p = real[i];
            str += p.to_string() + ", ";
        }
        const Point& p = real.back();
        str += p.to_string() + ")";

        return str;
    }

    virtual const ShapeType type() const override {
        return ShapeType::Polygon;
    }
};

#endif  // POLYGON_H
