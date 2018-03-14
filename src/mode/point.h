#ifndef POINT_H
#define POINT_H

#include <vector>
#include <string>
#include <exception>

class Point : public std::vector<double> {
public:
    Point() : std::vector<double>() {}

    explicit Point(std::vector<double> coords) : std::vector<double>(coords) {
        push_back(1);

        if (coords.size() < 2) {
            throw std::invalid_argument("Point must have, at least, 2 dimensions");
        }
    }

    // 2D point
    Point(double x, double y) : std::vector<double>() {
        push_back(x);
        push_back(y);
        push_back(1);
    }

    int dimensions() const {
        return size() - 1;
    }

    std::string to_string() const {

        if (size() == 0) {
            return "Point()";
        }

        std::string s = "Point(";
        int total_dimensions = size() - 1;

        for (int i = 0; i < total_dimensions - 1; i++) {
            s.append(std::to_string(at(i)));
            s.append(", ");
        }

        s.append(std::to_string(at(total_dimensions - 1)));
        s.append(")");
        return s;
    }
};

#endif  // POINT_H
