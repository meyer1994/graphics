#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <string>
#include "point.h"

class Shape {
public:
    Shape() {}

    explicit Shape(std::vector<Point> p) : points_real(p) {}

    ~Shape() {}


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
        for (Point& p : points_real) {
            p.scale(ratio);
        }
    }

    void rotate(double angle) {
        for (Point& p : points_real) {
            p.rotate(angle);
        }
    }

    void translate(double x, double y) {
        for (Point& p : points_real) {
            p.translate(x, y);
        }
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
            p.transform(m);
        }
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
};

#endif  // SHAPE_H