#ifndef WINDOW_H
#define WINDOW_H

#include <cmath>
#include <vector>

#include <gtkmm/builder.h>
#include <cairomm/context.h>
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
	Window(Glib::RefPtr<Gtk::Builder>& b, std::vector<Shape>& s)
    : shapes(s) {
        b->get_widget("drawing_area", drawing_area);

        Gtk::Allocation a = drawing_area->get_allocation();
        double x = a.get_width();
        double y = a.get_height();

        // Initial window size, matches the size of the drawing area
        rectangle = Shape(std::vector<Point>{
            Point(0, 0),
            Point(x, 0),
            Point(x, y),
            Point(0, y)
        });

        drawing_area
            ->signal_draw()
            .connect(sigc::mem_fun(*this, &Window::on_draw));
	}

	~Window() {}

    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
        // Configuration for dots to appear when drawn
        cr->set_line_cap(Cairo::LINE_CAP_ROUND);

        // Paints background in white
        cr->set_source_rgb(1, 1, 1);
        cr->paint();

        // Changes color to red
        cr->set_source_rgb(0.8, 0, 0);

        // Draw all shapes
        Matrix m = normalization_matrix();
        for (Shape s : shapes) {
            draw_shape(cr, s, m);
        }
        cr->stroke();

        return true;
    }

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

    Shape rectangle;
    std::vector<Shape>& shapes;
    Gtk::DrawingArea* drawing_area = nullptr;

protected:
    void draw_shape(const Cairo::RefPtr<Cairo::Context>& cr, Shape& shape, const Matrix& m) {
        // First point
        Point p0 = shape.real[0];
        p0.transform(m);
        Point p0v = vp_transform(p0);
        cr->move_to(p0v[0], p0v[1]);

        shape.window.clear();

        // Lines to other points
        for (Point point : shape.real) {
            point.transform(m);
            shape.window.push_back(point);
            Point n = vp_transform(point);
            cr->line_to(n[0], n[1]);
        }

        // Line from last point to first point
        cr->line_to(p0v[0], p0v[1]);
    }

    const Matrix normalization_matrix() {
        // Translation matrix
        Point medium = rectangle.medium();
        Vector t{-medium[0], -medium[1]};
        Matrix translate = Transformation::translate(t);

        // Rotation matrix
        Matrix rotate = Transformation::rotate(y_angle());

        // Scale matrix
        Gtk::Allocation a = drawing_area->get_allocation();
        double x_ratio = 1.0 / (width() / 2.0);
        double y_ratio = 1.0 / (height() / 2.0);
        Vector r{x_ratio, y_ratio};
        Matrix scale = Transformation::scale(r);

        // Combine transformations
        Matrix temp = Transformation::combine(translate, rotate);
        Matrix final = Transformation::combine(temp, scale);
        return final;
    }

    Point vp_transform(const Point& p) {
        Gtk::Allocation alloc = drawing_area->get_allocation();
        double xvmax = alloc.get_width();
        double yvmax = alloc.get_height();

        double x = ((p[0] + 1) / 2) * (xvmax);
        double y = (1 - (p[1] + 1) / 2) * (yvmax);
        return Point(x, y);
    }
};

#endif  // WINDOW_H
