#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <string>
#include <vector>
#include <stdexcept>

#include "vector.h"

class Point : public Vector {
public:
    Point() : Vector{0, 0, 0} {}

    explicit Point(Vector coords) : Vector(coords) {}

    Point(double x, double y, double z = 0) : Vector{x, y, z} {}

    void transform(const Matrix& m) {
        // Temporary point to store new values
        Vector temp{0, 0, 0, 1};

        // Add one to end
        push_back(1);

        // Apply Transform matrix to point (multiply the matrices)
        for (int i = 0; i < size(); i++) {
            for (int j = 0; j < size(); j++) {
                temp[i] += (at(j) * m[j][i]);
            }
        }

        // Copy new values to this point
        *this = Point(temp);

        // Remove 1 from end
        pop_back();
        shrink_to_fit();
    }

    const std::string to_string() const {
        if (size() == 0) {
            return "Point()";
        }

        std::string str = "Point(";
        for (int i = 0; i < size() - 1; i++) {
            str += std::to_string(at(i)) + ", ";
        }
        str += std::to_string(back()) + ")";

        return str;
    }
};

#endif  // POINT_H