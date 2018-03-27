#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <vector>

#include "point.h"

class Shape {
public:
    Shape() {}

    explicit Shape(std::vector<Point> p) : real(p) {}

    ~Shape() {}

    Point medium() {
        if (real.size() == 0) {
            throw std::domain_error("There are no points in shape");
        }

        Vector point_medium(real[0].size(), 0);
        // Sum
        for (const Point& p : real) {
            for (int i = 0; i < p.size(); i++) {
                point_medium[i] += p[i];
            }
        }
        // Divide
        for (double& d : point_medium) {
            d /= real.size();
        }
        return Point(point_medium);
    }

    void scale(double ratio) {
        for (Point& p : real) {
            p.scale(ratio);
        }
    }

    void rotate(double angle) {
        for (Point& p : real) {
            p.rotate(angle);
        }
    }

    void rotate(double angle, Point p) {
        Vector v;
    	for (int i = 0; i < p.size(); i++) {
    		v.push_back(-p[i]);
    	}
        Matrix t_mat_go = Transformation::translate(v);
        Matrix r_mat = Transformation::rotate(angle);
        Matrix t_mat_come = Transformation::translate(p);
        Matrix temp = Transformation::combine(t_mat_go, r_mat);
        Matrix multi = Transformation::combine(temp, t_mat_come);
        transform(multi);
    }

    void translate(double x, double y) {
        for (Point& p : real) {
            p.translate(Vector{x, y});
        }
    }

    void inflate(double ratio) {

    	// Get distance to origin
        Point m_point = medium();

        Vector v;
        for (double d : m_point) {
            v.push_back(-d);
        }
    	Matrix m_to_origin = Transformation::translate(v);

    	// Scale matrix
    	Vector d = Vector(m_point.size(), ratio);
    	Matrix m_scale = Transformation::scale(d);

    	// Back to start
    	Matrix m_to_source = Transformation::translate(m_point);

    	// Apply
    	Matrix temp = Transformation::combine(m_to_origin, m_scale);
    	Matrix final = Transformation::combine(temp, m_to_source);
        transform(final);
    }

    virtual const std::string to_string() const {
        int total = real.size();
        std::string str = "Shape(";
        for (int i = 0; i < total - 1; i++) {
            str.append(real[i].to_string());
            str.append(", ");
        }
        str.append(real[total - 1].to_string());
        str.append(")");
        return str;
    }

    int size() const {
        return real.size();
    }

    const Point& operator[](int i) const {
        return real[i];
    }

    Point& operator[](int i) {
        return real[i];
    }

    void transform(Matrix& m) {
        for (Point& p : real) {
            p.transform(m);
        }
    }

    std::vector<Point> real;
    std::vector<Point> window;

};

#endif  // SHAPE_H
