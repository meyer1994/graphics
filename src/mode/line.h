#ifndef LINE_H
#define LINE_H

#include <string>
#include <vector>

#include <cairomm/context.h>

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

    Line(std::string name) : Shape(name) {}

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

    virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr) const override {
        const Point& a = window[0];
        const Point& b = window[1];

        cr->move_to(a[0], a[1]);
        cr->line_to(b[0], b[1]);
    }
};

#endif  // LINE_H
