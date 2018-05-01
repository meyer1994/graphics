#ifndef LINE_SEGMENT_H
#define LINE_SEGMENT_H

#include <string>
#include <vector>
#include <stdexcept>

#include "point.h"
#include "base_shape.h"

class LineSegment : public BaseShape {
public:
    LineSegment() : BaseShape(name = "line") {}

    LineSegment(std::string name) : BaseShape(name) {}

    LineSegment(Point a, Point b, std::string name = "line")
    : BaseShape({a, b}, name, false) {
        if (a.size() != b.size()) {
            throw std::invalid_argument("Points must have same number of dimensions");
        }
    }

    virtual ~LineSegment() {}

    virtual const std::string to_string() const override {
        if (real.empty()) {
            return std::string("LineSegment()");
        }

        std::string str = "LineSegment(";
        str += real[0][0].to_string() + ", ";
        str += real[0][1].to_string() + ")";
        return str;
    }

    virtual const ShapeType type() const override {
        return ShapeType::LineSegment;
    }
};

#endif  // LINE_SEGMENT_H
