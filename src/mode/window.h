#ifndef WINDOW_H
#define WINDOW_H

#include <cmath>
#include <vector>

#include "shapes/polygon.h"

namespace Mode {


class Window : public Polygon {
public:
    Window() : Polygon("window") {}

	Window(std::vector<Point> p) : Polygon(p, "window") {}

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

    const double z_angle() const {
    	const Vector w = normal();
    	return w.angle({1.0, 0.0, 0.0});
    }

    const Vector normal() const {
    	const Point a = real[0];
		const Point b = real[1];
		const Point c = real[2];
		return -Vector::cross(b - a, c - a) / 2;
    }

    const Matrix parallel_matrix() const {
		const Vector norm = normal();

		// Rotation
		double tetax = std::atan(norm[1] / norm[2]);
		double tetay = std::atan(norm[0] / norm[2]);

		tetax = (180.0 / MATH_PI) * tetax;
		tetay = (180.0 / MATH_PI) * tetay;

		// Scale matrix
        double x_ratio = 1.0 / (width() / 2.0);
        double y_ratio = 1.0 / (height() / 2.0);

        // Just to draw the shape for easier clipping validation
        x_ratio *= 0.9;
        y_ratio *= 0.9;

		// Translate
		const Matrix tran = Transform::translate(-medium);
		const Matrix rotx = Transform::rotatex(tetax);
		const Matrix roty = Transform::rotatey(tetay);
        const Matrix scale = Transform::scale(x_ratio, y_ratio, 1.0);


		return tran * rotx * roty * scale;
    }

};

}  // namespace Mode

#endif  // WINDOW_H
