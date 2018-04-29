#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <string>
#include <vector>
#include <stdexcept>
#include <initializer_list>

#include "vector.h"

class Point : public Vector {
public:
    Point() : Vector{0, 0, 0, 1} {}

    Point(Vector coords) : Vector(coords) {}

    Point(std::initializer_list<double> d) : Vector(d) {}

    Point(double x, double y, double z = 0, double w = 1) : Vector{x, y, z, w} {}

    virtual ~Point() {}

    void transform(const Matrix& m) {
        // Temporary point to store new values
        Vector temp(size(), 0);

        // Apply Transform matrix to point (multiply the matrices)
        for (int i = 0; i < size(); i++) {
            for (int j = 0; j < size(); j++) {
                temp[i] += (at(j) * m[j][i]);
            }
        }

        // Copy new values to this point
        *this = (temp / back());
    }

    static const double distance(const Point& a, const Point& b) {
    	if (a.size() != b.size()) {
    		throw std::invalid_argument("Points must be of same order");
    	}

    	double res = 0;
    	for (int i = 0; i < a.size(); i++) {
    		const double ai = a[i];
    		const double bi = b[i];
    		res += ((ai - bi) * (ai - bi));
    	}
    	return std::sqrt(res);
    }

    const double distance(const Point& a) const {
    	return distance(*this, a);
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
