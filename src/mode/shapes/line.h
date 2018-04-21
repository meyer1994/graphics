#ifndef LINE_H
#define LINE_H

#include <string>
#include <vector>

#include "point.h"
#include "shape.h"

/**
 * @class Line class.
 *
 * @details Used to draw single lines in the drawing area.
 */
class Line : public Shape {
public:
    /**
     * @brief Default constructor.
     */
    Line() : Shape(name = "line") {}

    explicit Line(std::string name) : Shape(name) {}

    /**
     * @brief 2 point constructor.
     *
     * @param a Start point.
     * @param b End point.
     */
    Line(Point a, Point b, std::string name = "line")
    : Shape(std::vector<Point>{a, b}, name) {}

    virtual ~Line() {}

    /**
     * @brief To string method.
     *
     * @return String representation fo this class.
     */
    virtual const std::string to_string() const override {
        if (real.empty()) {
            return "Line()";
        }

        std::string str = "Line(";
        str += real[0].to_string() + ", ";
        str += real[1].to_string() + ")";

        return str;
    }

    virtual const Type2D type() const override {
        return Type2D::Line;
    }

    virtual const bool operator==(const Line& l) {
    	bool pa = real[0] == l.real[0];
    	bool pb = real[1] == l.real[1];

    	return pa && pb;
    }
};

#endif  // LINE_H
