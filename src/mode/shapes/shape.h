#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <vector>
#include <initializer_list>


#include "point.h"
#include "../transform.h"

enum class Type2D { Dot, Line, Polygon, BezierCurve, Spline };

class Shape {
public:
    Shape() : name("shape") {}

    Shape(std::string name) : name(name) {}

    Shape(std::initializer_list<Point> d)
    : real(d),
      name("shape") {
      	medium = calculate_medium();
      }

    Shape(std::vector<Point> p, std::string name = "shape")
    : real(p),
      name(name) {
      	medium = calculate_medium();
      }

    virtual ~Shape() {}

	virtual void rotate(const double x, const double y, const double z) {
		const Matrix rx = Transform::rotatex(x);
		const Matrix ry = Transform::rotatey(y);
		const Matrix rz = Transform::rotatez(z);

		const Matrix r = rx * ry * rz;
		transform(r);
	}

	virtual void rotate(const double angle, const Vector& v) {
		const Matrix rot = Transform::rotate(angle, v);
		transform(rot);
	}

	virtual void scale(const double ratio) {
		const Matrix s = Transform::scale(ratio, ratio, ratio);
		transform(s);
	}

	virtual void translate(const double x, const double y, const double z) {
		const Matrix t = Transform::translate(x, y, z);
		transform(t);
	}

    virtual void transform(const Matrix& m) {
    	for (Point& p : real) {
    		p.transform(m);
    	}
    	medium.transform(m);
    }

    virtual const bool operator==(const Shape& s) const = 0;

    virtual const bool operator!=(const Shape& s) const {
    	return !((*this) == s);
    }

    virtual const std::string to_string() const = 0;

    virtual const Type2D type() const = 0;

    std::string name;
    bool filled = false;

    Point medium;
    std::vector<Point> real;
    std::vector<Point> window;

protected:
	Point calculate_medium() {
		Vector m{0, 0, 0};
		for (Point& p : real) {
			m = m + p;
		}
		m = m / real.size();
		return Point(m);
	}
};

#endif  // SHAPE_H
