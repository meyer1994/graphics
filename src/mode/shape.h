#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <string>
#include <cmath>
#include <exception>
#include "point.h"

typedef std::vector<std::vector<double>> Matrix;
const double MATH_PI = std::acos(-1);

class Shape {
public:
    Shape() {}

    explicit Shape(std::vector<Point> p) : points_real(p) {}

    Point medium() {
        if (points_real.size() == 0) {
            throw std::domain_error("There are no points in shape");
        }

        std::vector<double> point_medium(points_real[0].dimensions(), 0);
        // Sum
        for (const Point& p : points_real) {
            for (int i = 0; i < p.size(); i++) {
                point_medium[i] += p[i];
            }
        }
        // Divide
        for (double& d : point_medium) {
            d /= points_real.size();
        }
        return Point(point_medium);
    }

    void scale(double ratio) {
        std::vector<double> r(points_real[0].dimensions(), ratio);
        transform(scale_matrix(r));
    }

    void rotate(double angle) {
        transform(rotate_matrix(points_real[0].dimensions(), angle));
    }

    void translate(double x, double y) {
        std::vector<double> t{x, y};
        transform(translate_matrix(t));
    }

    virtual std::string to_string() const {
        int total = points_real.size();
        std::string str = "Shape(";
        for (int i = 0; i < total - 1; i++) {
            str.append(points_real[i].to_string());
            str.append(", ");
        }
        str.append(points_real[total - 1].to_string());
        str.append(")");
        return str;
    }

    int size() const {
        return points_real.size();
    }

    std::vector<Point> points_real;
    std::vector<Point> points_window;

protected:
    void transform(Matrix m) {
        for (Point& p : points_real) {
            p = p_multiply(p, m);
        }
    }

    Matrix translate_matrix(std::vector<double>& v) {
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

    Matrix scale_matrix(std::vector<double>& v) {
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

    Matrix rotate_matrix(int dim, double angle) {
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

    Matrix m_multiply(Matrix& m0, Matrix& m1) {
        Matrix res(m0.size(), std::vector<double>(m0.size(), 0));

        for (int i = 0; i < res.size(); i++) {
            for (int j = 0; j < res.size(); j++) {
                for (int k = 0; k < res.size(); k++) {
                    res[i][j] += (m0[i][k] * m1[k][j]);
                }
            }
        }

        return res;
    }

    Point p_multiply(Point& p, Matrix& m) {
        Point new_point;

        for (int i = 0; i < p.size(); i++) {
            double value = 0;
            for (int j = 0; j < p.size(); j++) {
                value = value + (p[j] * m[j][i]);
            }
            new_point.push_back(value);
        }

        return new_point;
    }

};

#endif  // SHAPE_H
