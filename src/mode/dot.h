#ifndef DOT_H
#define DOT_H

#include "shape.h"

class Dot : public Shape {
public:
    Dot() : Shape() {}

    Dot(double x, double y) : Shape(std::vector<Point>{Point(x, y)}) {}

    std::string to_string() {
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
