#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <vector>

#include "point.h"

enum class Type2D { Dot, Line, Polygon, BezierCurve, Spline };

class Shape {
public:
    Shape() : name("shape") {}

    explicit Shape(std::string name) : name(name) {}

    Shape(std::vector<Point> p, std::string name = "shape")
    : real(p),
      name(name) {}

    virtual ~Shape() {}

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

    void translate(double x, double y, double z) {
        for (Point& p : real) {
            p.translate(Vector{x, y, z});
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

    virtual const std::string to_string() const = 0;

    virtual const Type2D type() const = 0;

    std::vector<Point> real;
    std::vector<Point> window;

    bool filled = false;

    std::string name;
};

#endif  // SHAPE_H
