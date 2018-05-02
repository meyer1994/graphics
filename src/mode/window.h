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
    	Vector h = real[3] - real[0];
        h.pop_back();
        return h.angle({0.0, 1.0, 0.0});
    }

    const double x_angle() const {
    	Vector w = real[1] - real[0];
        w.pop_back();
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

    const Matrix perspective_matrix() const {
        const double d = Point::distance(proj, medium);
        return Matrix{
            {1.0, 0.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 0.0, 1.0, 1.0/d},
            {0.0, 0.0, 0.0, 0.0}
        };
    }

    const Matrix projection_matrix() const {
        const Vector norm = normal();

        // Rotation
        double tetax = std::atan(norm[1] / norm[2]);
        double tetay = std::atan(norm[0] / norm[2]);

        tetax = (180.0 / MATH_PI) * tetax;
        tetay = (180.0 / MATH_PI) * tetay;

        // Scale matrix
        const double w = width();
        const double h = height();

        double x_ratio = 1.0 / (w / 2.0);
        double y_ratio = 1.0 / (h / 2.0);

        // Just to draw the shape for easier clipping validation
        x_ratio *= 0.9;
        y_ratio *= 0.9;

        const Matrix tran = Transform::translate(-proj);
        const Matrix rotx = Transform::rotatex(tetax);
        const Matrix roty = Transform::rotatey(tetay);
        const Matrix pers = perspective_matrix();
        const Matrix scale = Transform::scale(x_ratio, y_ratio, 1.0);

        return tran * rotx * roty * pers * scale;
    }

    // Value must be between 0 and 100
    void set_perspective(const double value) {
        if (value <= 0) {
            proj[2] = BASIS_PERSPECTIVE;
            return;
        }

        if (value >= 100) {
            proj[2] = BASIS_PERSPECTIVE * 100;
            return;
        }

        proj[2] = BASIS_PERSPECTIVE * value;
    }

    Point proj{medium[0], medium[1], -1000, 1};

    // constexpr because of reasons (cpp)
    static constexpr double BASIS_PERSPECTIVE = -100;
};

}  // namespace Mode

#endif  // WINDOW_H
