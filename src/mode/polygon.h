#ifndef POLYGON_H
#define POLYGON_H

#include <string>
#include <vector>

#include "shape.h"

class Polygon : public Shape {
public:
    Polygon() : Shape() {}

    explicit Polygon(std::vector<Point> points) : Shape(points) {}

    virtual std::string to_string() const override {
        if (points_real.size() == 0) {
            return "Polygon()";
        }
        std::string str = "Polygon(";
        for (int i = 0; i < size() - 1; i++) {
            str.append(points_real.at(i).to_string());
            str.append(", ");
        }
        str.append(points_real.back().to_string());
        str.append(")");
        return str;
    }
};

#endif  // POLYGON_H
