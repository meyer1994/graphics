#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <cmath>

#include "shapes/vector.h"

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

	if (v[1] == 0 && v[2] == 0) {
		return rotatex(angle);
	}
	if (v[0] == 0 && v[2] == 0) {
		return rotatey(angle);
	}
	if (v[0] == 0 && v[1] == 0) {
		return rotatez(angle);
	}

	// Convert to radians
	const double radian = angle * (MATH_PI / 180.0);

	const double angleY = Vector({0, v[1], v[2]}).angle({0, 0, 1});
	const double angleX = Vector({v[0], 0, v[2]}).angle({0, 0, 1});

	const Matrix t0  = translate(-v);
	const Matrix rx0 = rotatex(angleY);
	const Matrix ry0 = rotatey(-angleX);
	const Matrix rz  = rotatez(angle);
	const Matrix ry1 = rotatey(angleX);
	const Matrix rx1 = rotatex(-angleY);
	const Matrix t1  = translate(v);

	return t0 * ry0 * rx0 * rz * rx1 * ry1 * t1;
}

}  // namespace Transform

#endif  // TRANSFORM_H
