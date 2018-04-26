#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <cmath>

#include "vector.h"

// Constant
const double MATH_PI = std::acos(-1.0);

namespace Transform {

const Matrix translate(const double x, const double y, const double z) {
    return Matrix{
    	Vector{1.0, 0.0, 0.0, 0.0},
    	Vector{0.0, 1.0, 0.0, 0.0},
    	Vector{0.0, 0.0, 1.0, 0.0},
    	Vector{  x,   y,   z, 1.0}
    };
}

const Matrix translate(const Vector& v) {
	return translate(v[0], v[1], v[2]);
}

const Matrix scale(const double x, const double y, const double z) {
    return Matrix{
    	Vector{  x, 0.0, 0.0, 0.0},
    	Vector{0.0,   y, 0.0, 0.0},
    	Vector{0.0, 0.0,   z, 0.0},
    	Vector{0.0, 0.0, 0.0, 1.0}
    };
}

const Matrix rotatex(const double angle) {
    const double radian = (angle * MATH_PI) / 180.0;
    const double c = std::cos(radian);
    const double s = std::sin(radian);
    return Matrix{
        Vector{1.0, 0.0, 0.0, 0.0},
        Vector{0.0,   c,   s, 0.0},
        Vector{0.0,  -s,   c, 0.0},
        Vector{0.0, 0.0, 0.0, 1.0}
    };
}

const Matrix rotatey(const double angle) {
    const double radian = (angle * MATH_PI) / 180.0;
    const double c = std::cos(radian);
    const double s = std::sin(radian);
    return Matrix{
        Vector{  c, 0.0,  -s, 0.0},
        Vector{0.0, 1.0, 0.0, 0.0},
        Vector{  s, 0.0,   c, 0.0},
        Vector{0.0, 0.0, 0.0, 1.0}
    };
}

const Matrix rotatez(const double angle) {
    const double radian = (angle * MATH_PI) / 180.0;
    const double c = std::cos(radian);
    const double s = std::sin(radian);
    return Matrix{
        Vector{  c,   s, 0.0, 0.0},
        Vector{ -s,   c, 0.0, 0.0},
        Vector{0.0, 0.0, 1.0, 0.0},
        Vector{0.0, 0.0, 0.0, 1.0}
    };
}

const Matrix rotate(const double angle, const Vector& v) {
	// Convert to radians
	const double radian = (angle * MATH_PI) * 180.0;

	const double d = std::sqrt(v[1] * v[1] + v[2] * v[2]);
	const double calpha = v[2] / d;
	const double salpha = v[1] / d;
	const double cbeta = d;
	const double sbeta = v[0];

	const double angleY = Vector({0, v[1], v[2]}).angle({0, 0, 1});
	const double angleX = Vector({v[0], 0, v[2]}).angle({0, 0, 1});

	Matrix t0  = translate(v * -1.0);
	Matrix rx0;
	if (d != 0) {
		rx0 = rotatex(angleY);
	}
	Matrix ry0 = rotatey(-angleX);
	Matrix rz  = rotatez(angle);
	Matrix ry1 = rotatey(angleX);
	Matrix rx1;
	if (d != 0) {
		rx1 = rotatex(-angleY);
	}
	Matrix t1  = translate(v);

	if (d != 0) {
		return t0 * ry0 * rx0 * rz * rx1 * ry1 * t1;
	} else {
		return t0 * ry0 * rz * ry1 * t1;
	}
}

}  // namespace Transform

#endif  // TRANSFORM_H
