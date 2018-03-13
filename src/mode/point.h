#ifndef POINT_H
#define POINT_H

#include <vector>
#include <string>

class Point : public std::vector<double> {
public:
    Point() : std::vector<double>() {}

    Point(std::vector<double> coords) : std::vector<double>(coords) {
        push_back(1);
    }

    // 2D point
    Point(double x, double y) : std::vector<double>{x, y, 1} {}

    // 3D point
    Point(double x, double y, double z) : std::vector<double>{x, y, z, 1} {}

    const std::string to_string() const {

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