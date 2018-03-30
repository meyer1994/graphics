#ifndef WINDOW_H
#define WINDOW_H

#include <cmath>
#include <vector>

#include <gtkmm/builder.h>
#include <gtkmm/drawingarea.h>

#include "shape.h"

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
class Window {
public:
    /**
     * @brief Constructor.
     *
     * @param s Vector of shapes that are drawn into the viewport.
     */
	Window(Glib::RefPtr<Gtk::Builder>& b) {

		Gtk::DrawingArea* da = nullptr;
        b->get_widget("drawing_area", da);
        Gtk::Allocation a = da->get_allocation();
        double x = a.get_width();
        double y = a.get_height();

        // Initial window size, matches the size of the drawing area
        rectangle = Shape(std::vector<Point>{
            Point(0, 0),
            Point(x, 0),
            Point(x, y),
            Point(0, y)
        });
	}

	~Window() {}

    /**
     * @brief Gets the width of the window.
     *
     * @return Double representing the widht of the window in real world
     * coordinates.
     */
    const double width() const {
    	Point p0 = rectangle.real[0];
    	Point p1 = rectangle.real[1];
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
    	Point p0 = rectangle.real[0];
    	Point p1 = rectangle.real[3];
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
    	double x_vup = rectangle.real[3][0] - rectangle.real[0][0];
        double y_vup = rectangle.real[3][1] - rectangle.real[0][1];
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
        Point medium = rectangle.medium();
        Vector t{-medium[0], -medium[1]};
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

    Shape rectangle;

};

#endif  // WINDOW_H
