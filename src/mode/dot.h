#ifndef DOT_H
#define DOT_H

#include <string>
#include <vector>

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

    /**
     * @brief 2D contructor.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     */
    Dot(double x, double y, std::string name = "dot")
    : Shape(std::vector<Point>{Point(x, y)}, name) {}

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
        str.append(real[0].to_string());
        str.append(")");
        return str;
    }

    const Type type = Type::Dot;

};

#endif  // DOT_H
