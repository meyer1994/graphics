#ifndef POLYGON_H
#define POLYGON_H

#include <string>
#include <vector>

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
    Polygon() : Shape() {}

    /**
     * @brief Explicit constructor.
     * 
     * @details The last point of the vector will be connected with the first
     * point of the vector.
     * 
     * @param points Vector of points that make this polygon.
     */
    explicit Polygon(std::vector<Point> points) : Shape(points) {}

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
            str.append(real.at(i).to_string());
            str.append(", ");
        }
        str.append(real.back().to_string());
        str.append(")");
        return str;
    }
};

#endif  // POLYGON_H
