#ifndef CONTROL_VIEWPORT_H
#define CONTROL_VIEWPORT_H

#include <string>
#include <vector>
#include <iostream>
#include <exception>


#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/builder.h>
#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/comboboxtext.h>

#include "../mode/line.h"
#include "../mode/shape.h"
#include "../mode/point.h"
#include "../mode/window.h"
#include "../mode/clipping.h"

namespace Control {

class Viewport {
public:
    Viewport(Glib::RefPtr<Gtk::Builder>& b, std::vector<Shape>& s, Window& w)
    : window(w),
      shapes(s) {

        // Dummy shape (debugging)
        Shape dummy = Shape(std::vector<Point>{
            Point(0, 0),
            Point(50, 50),
            Point(50, 0)
        });
        dummy.fill = true;
        s.push_back(dummy);


        s.push_back(Line(Point(0, 0), Point(50, 50), "linhaaaaaa"));

        Gtk::ComboBoxText* c = nullptr;
        b->get_widget("combobox_shapes", c);
        c->append("teste");

        b->get_widget("drawing_area", drawing_area);

        // Rotation controls
        b->get_widget("input_angle", input_angle);
        b->get_widget("button_rotate_left", button_rotate_left);
        b->get_widget("button_rotate_right", button_rotate_right);

        // Movement controls
        b->get_widget("button_up", button_up);
        b->get_widget("button_down", button_down);
        b->get_widget("button_left", button_left);
        b->get_widget("button_right", button_right);
        b->get_widget("input_viewport_move", input_viewport_move);

        // Zoom controls
        b->get_widget("button_in", button_in);
        b->get_widget("button_out", button_out);
        b->get_widget("input_viewport_zoom", input_viewport_zoom);

        drawing_area
            ->signal_draw()
            .connect(sigc::mem_fun(*this, &Viewport::on_draw));

        connect_buttons();
    }

    ~Viewport() {}

    void move_up() {
        double move = get_move_input();
        double y_angle = window.y_angle();
        double y_move = std::cos(y_angle * _MATH_PI / 180) * move;
        double x_move = std::sin(y_angle * _MATH_PI / 180) * move;
        window.rectangle.translate(x_move, y_move);
        drawing_area->queue_draw();
    }

    void move_down() {
        double move = get_move_input();
        double y_angle = window.y_angle();
        double y_move = std::cos(y_angle * _MATH_PI / 180) * move;
        double x_move = std::sin(y_angle * _MATH_PI / 180) * move;
        window.rectangle.translate(-x_move, -y_move);
        drawing_area->queue_draw();
    }

    void move_left() {
		double move = get_move_input();
        double y_angle = window.y_angle();
        double y_move = std::cos(y_angle * _MATH_PI / 180) * move;
        double x_move = std::sin(y_angle * _MATH_PI / 180) * move;
        window.rectangle.translate(-y_move, x_move);
        drawing_area->queue_draw();
    }

    void move_right() {
		double move = get_move_input();
        double y_angle = window.y_angle();
        double y_move = std::cos(y_angle * _MATH_PI / 180) * move;
        double x_move = std::sin(y_angle * _MATH_PI / 180) * move;
        window.rectangle.translate(y_move, -x_move);
        drawing_area->queue_draw();
    }

    void zoom_in() {
        double zoom = get_zoom_input() / 100;
        window.rectangle.inflate(1 - zoom);
        drawing_area->queue_draw();
    }

    void zoom_out() {
        double zoom = get_zoom_input() / 100;
        window.rectangle.inflate(1 + zoom);
        drawing_area->queue_draw();
    }

    void rotate_right() {
        double angle = get_angle_input();
        Point medium = window.rectangle.medium();
        window.rectangle.rotate(-angle, medium);
        drawing_area->queue_draw();
    }

    void rotate_left() {
        double angle = get_angle_input();
        Point medium = window.rectangle.medium();
        window.rectangle.rotate(angle, medium);
        drawing_area->queue_draw();
    }

    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
        // Configuration for dots to appear when drawn
        cr->set_line_cap(Cairo::LINE_CAP_ROUND);

        // Paints background in white
        cr->set_source_rgb(1, 1, 1);
        cr->paint();

        // Transformation matrix
        Matrix m = window.normalization_matrix();

        // Change color to blue
        cr->set_source_rgb(0, 1, 1);
        normalize_shape(window.rectangle, m);
        draw_shape(cr, window.rectangle.window);
        cr->stroke();

        // Changes color to red
        cr->set_source_rgb(0.8, 0, 0);

        // Draw all shapes
        for (Shape s : shapes) {
        	normalize_shape(s, m);
        	clipper(s);
            draw_shape(cr, s.window);
            if (s.fill) {
            	cr->fill();
            }
	        cr->stroke();
        }

        return true;
    }

    Window& window;
    std::vector<Shape>& shapes;

    Clipping clip;

    Gtk::DrawingArea* drawing_area = nullptr;

    // Rotation controls
    Gtk::Entry* input_angle = nullptr;
    Gtk::Button* button_rotate_right = nullptr;
    Gtk::Button* button_rotate_left = nullptr;

    // Movement controls
    Gtk::Button* button_up = nullptr;
    Gtk::Button* button_left = nullptr;
    Gtk::Button* button_right = nullptr;
    Gtk::Button* button_down = nullptr;
    Gtk::Entry* input_viewport_move = nullptr;

    // Zoom controls
    Gtk::Button* button_in = nullptr;
    Gtk::Button* button_out = nullptr;
    Gtk::Entry* input_viewport_zoom = nullptr;

protected:
    void connect_buttons() {
        button_up
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Viewport::move_up));

        button_down
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Viewport::move_down));

        button_left
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Viewport::move_left));

        button_right
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Viewport::move_right));

        button_in
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Viewport::zoom_in));

        button_out
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Viewport::zoom_out));

        button_rotate_left
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Viewport::rotate_left));

        button_rotate_right
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Viewport::rotate_right));
    }

    double get_move_input() {
        double move_size = 10;
        try {
            std::string move_input = input_viewport_move->get_text();
            move_size = std::stod(move_input);

        } catch (std::exception& e) {
            // Nothing
        }
        return move_size;
    }

    double get_zoom_input() {
        double zoom_size = 10;
        try {
            std::string zoom_input = input_viewport_zoom->get_text();
            zoom_size = std::stod(zoom_input);

        } catch (std::exception& e) {
            // Nothing
        }
        return zoom_size;
    }

    double get_angle_input() {
        double angle = 30;
        try {
            std::string angle_input = input_angle->get_text();
            angle = std::stod(angle_input);
        } catch (std::exception& e) {
            // Nothing
        }
        return angle;
    }

    void normalize_shape(Shape& shape, Matrix& transformation) {
    	shape.window.clear();
    	for (Point p : shape.real) {
    		p.transform(transformation);
    		shape.window.push_back(p);
    	}
    }

    void draw_shape(const Cairo::RefPtr<Cairo::Context>& cr, std::vector<Point>& points) {
        if (points.empty()) {
        	return;
        }

        // First point
        Point p0 = points[0];

        Point p0v = vp_transform(p0);
        cr->move_to(p0v[0], p0v[1]);

        // Lines to other points
        for (Point point : points) {
            Point n = vp_transform(point);
            cr->line_to(n[0], n[1]);
        }

        // Line from last point to first point
        cr->line_to(p0v[0], p0v[1]);
    }

    Point vp_transform(const Point& p) {
        Gtk::Allocation alloc = drawing_area->get_allocation();
        double xvmax = alloc.get_width();
        double yvmax = alloc.get_height();

        double x = ((p[0] + 1) / 2) * (xvmax);
        double y = (1 - (p[1] + 1) / 2) * (yvmax);
        return Point(x, y);
    }

    void clipper(Shape& shape) {

		// Dot
    	if (shape.size() == 1) {
    		return clip.dot(shape);
    	}

		// Line
    	if (shape.size() == 2) {
    		// return clip.cohen_sutherland(shape);
    		return clip.liang_barsky(shape);
    	}

    	// Polygon
    	clip.sutherland_hodgman(shape);
    }
};

}  // namespace Control


#endif  // CONTROL_VIEWPORT_H
