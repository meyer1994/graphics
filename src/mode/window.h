#ifndef WINDOW_H
#define WINDOW_H

#include <cmath>
#include <vector>

#include <gtkmm/builder.h>
#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>

#include "shape.h"

class Window {
public:
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
        Matrix m = transformation();
        for (Shape s : shapes) {
            draw_shape(cr, s, m);
        }
        cr->stroke();

        return true;
    }

    Shape rectangle;
    std::vector<Shape>& shapes;
    Gtk::DrawingArea* drawing_area = nullptr;

protected:
    double xmax() {
        return rectangle.points_real[2][0];
    }

    double ymax() {
        return rectangle.points_real[2][1];
    }

    double xmin() {
        return rectangle.points_real[0][0];
    }

    double ymin() {
        return rectangle.points_real[0][1];
    }

    void draw_shape(const Cairo::RefPtr<Cairo::Context>& cr, const Shape& shape, const Matrix& m) {
        // First point
        Point p0 = shape.points_real[0];
        p0.transform(m);
        Point p0v = vp_transform(p0);
        cr->move_to(p0v[0], p0v[1]);

        // Lines to other points
        for (Point point : shape.points_real) {
            point.transform(m);
            Point n = vp_transform(point);
            cr->line_to(n[0], n[1]);
        }

        // Line from last point to first point
        cr->line_to(p0v[0], p0v[1]);
    }

    const Matrix transformation() {
        // Translation matrix
        double x_medium = (xmax() + xmin()) / 2;
        double y_medium = (ymax() + ymin()) / 2;
        Vector t{-x_medium, -y_medium};
        Matrix translate = Transformation::translate(t);

        // Rotation matrix
        // Copied from:
        // https://stackoverflow.com/questions/21483999
        double radian = std::atan2(1.0, 0.0) - std::atan2(ymax(), xmin());
        double angle = radian * (180.0 / _MATH_PI);
        Matrix rotate = Transformation::rotate(angle);

        // Scale matrix
        Gtk::Allocation a = drawing_area->get_allocation();
        double x_ratio = 1.0 / (a.get_width() / 2.0);
        double y_ratio = 1.0 / (a.get_height() / 2.0);
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

        double x = ((p[0] - -1) / (1 - -1)) * (xvmax);
        double y = (1 - ((p[1] - -1) / (1 - -1))) * (yvmax);
        return Point(x, y);
    }
};

#endif  // WINDOW_H
