#ifndef DOT_H
#define DOT_H

#include <string>
#include <vector>

#include "shape.h"

class Dot : public Shape {
public:
    Dot() : Shape() {}

    Dot(double x, double y) : Shape(std::vector<Point>{Point(x, y)}) {}

    virtual std::string to_string() const {
        if (points_real.size() == 0) {
            return "Dot()";
        }
        std::string str = "Dot(";
        str.append(points_real[0].to_string());
        str.append(")");
        return str;
    }

};

#endif  // DOT_H
