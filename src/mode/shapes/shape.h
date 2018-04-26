#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <vector>

#include "point.h"
#include "../transform.h"

enum class Type2D { Dot, Line, Polygon, BezierCurve, Spline };

class Shape {
public:
    Shape() : name("shape") {}

    explicit Shape(std::string name) : name(name) {}

    virtual ~Shape() {}

	virtual void rotate(double x, double y, double z) {
		const Matrix rx = Transform::rotatex(x);
		const Matrix ry = Transform::rotatey(y);
		const Matrix rz = Transform::rotatez(z);

		const Matrix r = rx * ry * rz;
		transform(r);
	}

	virtual void scale(double ratio) {
		const Matrix s = Transform::scale(ratio, ratio, ratio);
		transform(s);
	}

	virtual void translate(double x, double y, double z) {
		const Matrix t = Transform::translate(x, y, z);
		transform(t);
	}

    virtual void transform(const Matrix& m) = 0;

    virtual const std::string to_string() const = 0;

    virtual const Type2D type() const = 0;

    Point medium;
    std::string name;
};

#endif  // SHAPE_H
