#ifndef DOT_H
#define DOT_H

#include <string>
#include <vector>

#include "point.h"
#include "shape.h"

/**
 * @class Dot class.
 *
 * @details Used to draw dots in the drawing area.
 */
class Dot : public Shape {
public:
    /**
     * @brief Default constructor.
     */
    Dot() : Shape(name = "dot") {}

    Dot(std::string name) : Shape(name) {}

    /**
     * @brief 2D contructor.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     */
    Dot(double x, double y, std::string name = "dot")
    : Shape(std::vector<Point>{Point(x, y)}, name) {}

    Dot(Point point, std::string name = "dot")
    : Shape(std::vector<Point>{point}, name) {}

    virtual ~Dot() {}

    /**
     * @brief To string method.
     *
     * @return An string representing this class.
     */
    virtual const std::string to_string() const override {
        if (real.size() == 0) {
            return "Dot()";
        }

        std::string str = "Dot(";
        str += real[0].to_string();
        str += ")";

        return str;
    }

    virtual const Type2D type() const override {
        return Type2D::Dot;
    }
};

#endif  // DOT_H
