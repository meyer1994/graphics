#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <vector>
#include <string>
#include <cmath>
#include "point.h"

typedef std::vector<std::vector<double>> Matrix;

const long double _MATH_PI = 3.141592653589793238463;

class Drawable {
public:
    Drawable() {}

    virtual const Point medium() const = 0;

    static const Matrix translate_matrix(const std::vector<double>& v) {
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

    static const Matrix scale_matrix(const std::vector<double>& v) {
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

    static const Matrix rotate_matrix(const int& dim, const double& angle) {
        if (dim > 3) {
            throw std::invalid_argument("Rotations for more than 3 dimensions not supported");
        }

        if (dim < 2) {
            throw std::invalid_argument("Rotations for less than 2 dimensions not supported");
        }

        // 2 dimensions
        if (dim == 2) {
            double c = std::cos((angle * _MATH_PI) / 180);
            double s = std::sin((angle * _MATH_PI) / 180);
            return Matrix{
                std::vector<double>{c, -s, 0},
                std::vector<double>{s,  c, 0},
                std::vector<double>{0,  0, 1}
            };
        }
    
        // 3 dimensions
        throw std::invalid_argument("TODO 3 dimensional rotation");
    }

    static const Matrix m_multiply(const Matrix& m0, const Matrix& m1) {
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

    static const Point p_multiply(const Point& p, const Matrix& m) {
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

    virtual void scale() {}

    virtual void rotate() {}

    virtual void translate() {}

    virtual void transform(const Matrix& m) = 0;

    virtual const std::string to_string() const = 0;

    // void move(double x, double y) {
    //     Point m = get_medium_point();
    //     for (Point& p : points) {
    //         p.x = p.x - m.x + x;
    //         p.y = p.y - m.y + y;
    //     }
    // }

    // void inflate(double s) {
    //     Point medium = get_medium_point();
    //     move(0, 0);
    //     scale(s);
    //     move(medium.x, medium.y);
    // }

    // void scale(double s) {
    //     for (Point& p : points) {
    //         p.x *= s;
    //         p.y *= s;
    //     }
    // }

    // void translate(double x, double y) {
    //     Point m = get_medium_point();
    //     move(m.x + x, m.y + y);
    // }

};

#endif  // DRAWABLE_H