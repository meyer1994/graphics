#ifndef POLYGON_H
#define POLYGON_H

#include <string>
#include <vector>

#include <cairomm/context.h>

#include "point.h"
#include "shape.h"

/**
 * @brief Polygon class.
 *
 * @details Class used to draw polygons into the drawing area.
 */
class Polygon : public Shape {
public:
    /**
     * @brief Default constructor.
     */
    Polygon() : Shape(name = "polygon") {}


    Polygon(std::string name) : Shape(name) {}

    /**
     * @brief Explicit constructor.
     *
     * @details The last point of the vector will be connected with the first
     * point of the vector.
     *
     * @param points Vector of points that make this polygon.
     */
    Polygon(std::vector<Point> points, std::string name = "polygon")
    : Shape(points, name) {}

    virtual ~Polygon() {}

    /**
     * @brief To string method.
     *
     * @return Representation of this class.
     */
    virtual const std::string to_string() const override {
        if (real.size() == 0) {
            return "Polygon()";
        }

        std::string str = "Polygon(";

        for (int i = 0; i < size() - 1; i++) {
            const Point& p = real.at(i);
            str += p.to_string() + ", ";
        }

        const Point& p = real.back();
        str += p.to_string() + ")";

        return str;
    }

    virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr) const override {
        const Point& first = window.front();
        cr->move_to(first[0], first[1]);

        for (int i = 1; i < window.size(); i++) {
            const Point& p = window[i];
            cr->line_to(p[0], p[1]);
        }

        cr->line_to(first[0], first[1]);
    }

    bool filled == false;

};

#endif  // POLYGON_H
