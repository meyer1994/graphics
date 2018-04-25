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

    virtual ~Shape() {}

	virtual void rotate(double x, double y, double z) {
		const Matrix rx = Transformation::rotatex(x);
		const Matrix ry = Transformation::rotatey(y);
		const Matrix rz = Transformation::rotatez(z);

		const Matrix r0 = Transformation::multiply(rx, ry);
		const Matrix r1 = Transformation::multiply(r0, rz);

		transform(r1);
	}

	virtual void scale(double ratio) {
		const Matrix s = Transformation::scale(ratio, ratio, ratio);
		transform(s);
	}

	virtual void translate(double x, double y, double z) {
		const Matrix t = Transformation::translate(x, y, z);
		transform(t);
	}

    virtual void transform(const Matrix& m) = 0;

    virtual const std::string to_string() const = 0;

    virtual const Type2D type() const = 0;

    Point medium;
    std::string name;
};

#endif  // SHAPE_H
