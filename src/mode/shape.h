#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <vector>

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

        Vector point_medium(points_real[0].size(), 0);
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
        for (Point& p : points_real) {
            p.translate(Vector{x, y});
        }
    }

    void inflate(double ratio) {

    	// Get distance to origin
    	Point m_point = medium();
    	Vector v;
    	for (int i = 0; i < m_point.size(); i++) {
    		v.push_back(-m_point[i]);
    	}

    	// To origin matrix
    	Matrix m_origin = Transformation::translate(v);

    	// Scale matrix
    	Vector d = Vector(m_point.size(), ratio);
    	Matrix m_scale = Transformation::scale(d);

    	// Back to start
    	Matrix m_medium = Transformation::translate(m_point);

    	// Apply
    	Matrix temp = Transformation::combine(m_origin, m_scale);
    	Matrix m_transform = Transformation::combine(temp, m_medium);
    	for (Point& p : points_real) {
    		p.transform(m_transform);
    	}
    }

    virtual const std::string to_string() const {
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

    const Point& operator[](int i) const {
        return points_real[i];
    }

    Point& operator[](int i) {
        return points_real[i];
    }

    void transform(Matrix& m) {
        for (Point& p : points_real) {
            p.transform(m);
        }
    }

    std::vector<Point> points_real;

};

#endif  // SHAPE_H
