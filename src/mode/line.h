#ifndef LINE_H
#define LINE_H

#include <vector>
#include <string>

#include "shape.h"

class Line : public Shape {
public:
    Line() : Shape() {}

    Line(Point a, Point b) : Shape(std::vector<Point>{a, b}) {}

    std::string to_string() {
        if (points_real[0].size() == 0 || points_real[1].size() == 0) {
            return "Line()";
        }

        std::string s = "Line(";
        s.append(points_real[0].to_string());
        s.append(", ");
        s.append(points_real[1].to_string());
        s.append(")");
        return s;
    }
};

#endif  // LINE_H
