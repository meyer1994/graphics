#ifndef WINDOW_H
#define WINDOW_H

#include <cmath>
#include <vector>

#include "shapes/shape.h"

namespace Mode {


class Window : public Polygon {
public:
    Window() : Polygon("window") {}

	Window(double width, double heigth)
    : Polygon({
        Point(0, 0),
        Point(width, 0),
        Point(width, heigth),
        Point(0, heigth)
      }, "window") {}

	virtual ~Window() {}

    const double width() const {
    	return Point::distance(real[0], real[1]);
    }

    const double height() const {
    	return Point::distance(real[0], real[3]);
    }

    const double y_angle() const {
    	const Vector h = real[3] - real[0];
        return h.angle({0.0, 1.0, 0.0});
    }

    const double x_angle() const {
    	const Vector w = real[1] - real[0];
    	return w.angle({1.0, 0.0, 0.0});
    }

    const Matrix parallel_matrix() const {
		// Normal
		const Point a = real[0];
		const Point b = real[1];
		const Point m = medium;
		const Vector normal = Vector::cross(m - a, b - m);

		// Rotation
		double tetax = std::atan(normal[1] / normal[2]);
		double tetay = std::atan(normal[0] / normal[2]);

		// Convert to degrees
		tetax = (tetax * 180.0) / MATH_PI;
		tetay = (tetay * 180.0) / MATH_PI;

		// Translate
		const Matrix tran = Transform::translate(-medium);
		// Rotate
		const Matrix rotx = Transform::rotatex(tetax);
		const Matrix roty = Transform::rotatey(tetay);

		return tran * rotx * roty;
    }

    const Matrix normalization_matrix() const {
        // Translation matrix
        const Matrix translate = Transform::translate(-medium);

        // Rotation matrix
        const Matrix rotate = Transform::rotatey(y_angle());

        // Scale matrix
        double x_ratio = 1.0 / (width() / 2.0);
        double y_ratio = 1.0 / (height() / 2.0);

        // Just to draw the shape for easier clipping validation
        x_ratio *= 0.9;
        y_ratio *= 0.9;

        const Matrix scale = Transform::scale(x_ratio, y_ratio, 1);

        // Combine transformations
        return translate * rotate * scale;
    }
};

}  // namespace Mode

#endif  // WINDOW_H
