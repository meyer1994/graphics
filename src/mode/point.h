#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <vector>
#include <string>
#include <exception>

typedef std::vector<std::vector<double>> Matrix;
const double MATH_PI = std::acos(-1);

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

    void scale(double ratio) {
        std::vector<double> r(dimensions(), ratio);
        transform(scale_matrix(r));
    }

    void rotate(double angle) {
        transform(rotate_matrix(dimensions(), angle));
    }

    void translate(double x, double y) {
        std::vector<double> t{x, y};
        transform(translate_matrix(t));
    }

    void transform(Matrix m) {
        std::vector<double> v;

        // Apply transformation matrix to point
        for (int i = 0; i < size(); i++) {
            double value = 0;
            for (int j = 0; j < size(); j++) {
                value = value + (at(j) * m[j][i]);
            }
            v.push_back(value);
        }

        // Copy new values to this point
        for (int i = 0; i < size(); i++) {
            at(i) = v[i];
        }
    }

    static Matrix translate_matrix(std::vector<double>& v) {
        int total = v.size();

        // Creates TOTAL x TOTAL matrix
        Matrix matrix(total + 1, std::vector<double>(total + 1, 0));

        // Add 1s to main diagonal
        for (int i = 0; i < total + 1; i++) {
            matrix[i][i] = 1;
        }

        // Add translation line
        for (int i = 0; i < total; i++) {
            matrix[total][i] = v[i];
        }

        return matrix;
    }

    static Matrix scale_matrix(std::vector<double>& v) {
        int total = v.size();

        // Creates TOTAL x TOTAL matrix
        Matrix matrix(total + 1);
        for (std::vector<double>& v : matrix) {
            v = std::vector<double>(total + 1, 0);
        }

        // Add ratios to main diagonal
        for (int i = 0; i < total; i++) {
            matrix[i][i] = v[i];
        }

        matrix[total][total] = 1;

        return matrix;
    }

    static Matrix rotate_matrix(int dim, double angle) {
        if (dim > 3) {
            throw std::invalid_argument("Rotations for more than 3 dimensions not supported");
        }

        if (dim < 2) {
            throw std::invalid_argument("Rotations for less than 2 dimensions not supported");
        }

        // 2 dimensions
        if (dim == 2) {
            double c = std::cos((angle * MATH_PI) / 180);
            double s = std::sin((angle * MATH_PI) / 180);
            return Matrix{
                std::vector<double>{c, -s, 0},
                std::vector<double>{s,  c, 0},
                std::vector<double>{0,  0, 1}
            };
        }

        // 3 dimensions
        throw std::invalid_argument("TODO 3 dimensional rotation");
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
