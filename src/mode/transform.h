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
        Vector{1.0,  0.0, 0.0, 0.0},
        Vector{0.0,    c,   s, 0.0},
        Vector{0.0,   -s,   c, 0.0},
        Vector{0.0,  0.0, 0.0, 1.0}
    };
}

const Matrix rotatey(const double angle) {
    const double radian = (angle * MATH_PI) / 180.0;
    const double c = std::cos(radian);
    const double s = std::sin(radian);
    return Matrix{
        Vector{  c, 0.0,   -s, 0.0},
        Vector{0.0, 1.0,  0.0, 0.0},
        Vector{  s, 0.0,    c, 0.0},
        Vector{0.0, 0.0,  0.0, 1.0}
    };
}

const Matrix rotatez(const double angle) {
    const double radian = (angle * MATH_PI) / 180.0;
    const double c = std::cos(radian);
    const double s = std::sin(radian);
    return Matrix{
        Vector{   c,   s, 0.0, 0.0},
        Vector{  -s,   c, 0.0, 0.0},
        Vector{ 0.0, 0.0, 1.0, 0.0},
        Vector{ 0.0, 0.0, 0.0, 1.0}
    };
}

const Matrix rotate(const double angle, const Vector& v) {
	double d = v.length();
	double beta = std::atan(v[0] / v[2]);
	double alpha = std::atan(v[1] / d);

	// Convert to degrees
	beta = (beta * 180) / MATH_PI;
	alpha = (alpha * 180) / MATH_PI;

	Matrix t0  = translate(v * -1.0);
	Matrix ry0 = rotatey(-beta);
	Matrix rx0 = rotatex(alpha);
	Matrix rz  = rotatez(angle);
	Matrix rx1 = rotatex(-alpha);
	Matrix ry1 = rotatey(beta);
	Matrix t1  = translate(v);

	return t0 * ry0 * rx0 * rz * rx1 * ry1 * t1;
}

}  // namespace Transform

#endif  // TRANSFORM_H
