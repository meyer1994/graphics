#ifndef LINE_H
#define LINE_H

#include <string>
#include <vector>

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

    /**
     * @brief 2 point constructor.
     *
     * @param a Start point.
     * @param b End point.
     */
    Line(Point a, Point b, std::string name = "line")
    : Shape(std::vector<Point>{a, b}, name) {}

    /**
     * @brief To string method.
     *
     * @return String representation fo this class.
     */
    virtual const std::string to_string() const override {
        if (real[0].size() == 0 || real[1].size() == 0) {
            return "Line()";
        }
        std::string s = "Line(";
        s.append(real[0].to_string());
        s.append(", ");
        s.append(real[1].to_string());
        s.append(")");
        return s;
    }

    static const Type type = Type::Line;

};

#endif  // LINE_H
