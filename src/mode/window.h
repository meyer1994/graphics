#ifndef WINDOW_H
#define WINDOW_H

#include <cmath>
#include <vector>

#include "shape.h"

namespace Mode {

/**
 * @brief Window class.
 *
 * @details This object represents the window view of the real coordinates. The
 * coordinates inside this view are normalized in a way that the center of the
 * window is located at the point (0, 0) and the extremes are (-1, -1) and
 * (1, 1).
 *
 * @param s [description]
 */
class Window : public Polygon {
public:
    Window() : Polygon("window") {}
    /**
     * @brief Constructor.
     *
     * @param s Vector of shapes that are drawn into the viewport.
     */
	Window(double width, double heigth)
    : Polygon(std::vector<Point>{
        Point(0, 0),
        Point(width, 0),
        Point(width, heigth),
        Point(0, heigth)
    },  "window") {}

	virtual ~Window() {}

    /**
     * @brief Gets the width of the window.
     *
     * @return Double representing the widht of the window in real world
     * coordinates.
     */
    const double width() const {
    	Point p0 = real[0];
    	Point p1 = real[1];
    	double x = p0[0] - p1[0];
    	double y = p0[1] - p1[1];
    	return std::sqrt(x * x + y * y);
    }

    /**
     * @brief Gets the height of the window.
     *
     * @return Returns double representing the height of the window.
     */
    const double height() const {
    	Point p0 = real[0];
    	Point p1 = real[3];
    	double x = p0[0] - p1[0];
    	double y = p0[1] - p1[1];
    	return std::sqrt(x * x + y * y);
    }

    /**
     * @brief Gets the angle of the window related to the Y axis of the real
     * world.
     *
     * @return Double representing the angle, in degrees.
     */
    const double y_angle() const {
    	double x_vup = real[3][0] - real[0][0];
        double y_vup = real[3][1] - real[0][1];
        double cos = y_vup / std::sqrt(x_vup * x_vup + y_vup * y_vup);
        double radian = std::acos(cos);
        if(x_vup < 0) {
        	radian = -radian;
        }
        return (radian * 180.0) / _MATH_PI;
    }

    /**
     * @brief Same as y_angle, but for the X axis.
     */
    const double x_angle() const {
    	return 90 - y_angle();
    }

    const Matrix normalization_matrix() {
        // Translation matrix
        Point med = medium();
        Vector t{-med[0], -med[1]};
        Matrix translate = Transformation::translate(t);

        // Rotation matrix
        Matrix rotate = Transformation::rotate(y_angle());

        // Scale matrix
        double x_ratio = 1.0 / (width() / 2.0);
        double y_ratio = 1.0 / (height() / 2.0);

        // Just to draw the shape for easier clipping validation
        x_ratio *= 0.9;
        y_ratio *= 0.9;

        Vector r{x_ratio, y_ratio};
        Matrix scale = Transformation::scale(r);

        // Combine transformations
        Matrix temp = Transformation::combine(translate, rotate);
        Matrix final = Transformation::combine(temp, scale);
        return final;
    }
};

}  // namespace Mode

#endif  // WINDOW_H
