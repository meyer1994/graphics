#ifndef CONTROL_VIEWPORT_H
#define CONTROL_VIEWPORT_H

#include <string>
#include <vector>
#include <exception>

#include <cairomm/context.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/builder.h>
#include <gtkmm/drawingarea.h>

#include "../mode/shape.h"
#include "../mode/point.h"
#include "../mode/window.h"

namespace Control {

class Viewport {
public:
    Viewport(Glib::RefPtr<Gtk::Builder>& b, std::vector<Shape>& s, Window& w)
    : shapes(s),
      window(w) {

        // Dummy shape
        shapes.push_back(Shape(std::vector<Point>{
            Point(0, 0),
            Point(50, 0),
            Point(50, 50),
            Point(0, 50)
        }));

        b->get_widget("input_viewport_move", input_viewport_move);
        b->get_widget("input_viewport_zoom", input_viewport_zoom);
        b->get_widget("drawing_area", drawing_area);
        b->get_widget("button_up", button_up);
        b->get_widget("button_down", button_down);
        b->get_widget("button_left", button_left);
        b->get_widget("button_right", button_right);
        b->get_widget("button_in", button_in);
        b->get_widget("button_out", button_out);

        connect_buttons();
        connect_draw();
    }

    ~Viewport() {}

    void move_up() {
        window.ymax += get_move_input();
        window.ymin += get_move_input();
        drawing_area->queue_draw();
    }

    void move_down() {
        window.ymax -= get_move_input();
        window.ymin -= get_move_input();
        drawing_area->queue_draw();
    }

    void move_left() {
        window.xmax -= get_move_input();
        window.xmin -= get_move_input();
        drawing_area->queue_draw();
    }

    void move_right() {
        window.xmax += get_move_input();
        window.xmin += get_move_input();
        drawing_area->queue_draw();
    }

    void zoom_in() {
        double quo = (window.ymax - window.xmin)/(window.xmax - window.xmin);
        double zoom = get_zoom_input();
        window.ymax -= zoom * quo;
        window.xmax -= zoom;
        printf("xmin = %f\n", window.xmin);
        printf("xmax = %f\n", window.xmax);
        printf("ymin = %f\n", window.ymin);
        printf("ymax = %f\n", window.ymax);
        printf("quo = %f\n\n",  quo);
        drawing_area->queue_draw();
    }

    void zoom_out() {
        double quo = (window.ymax - window.xmin)/(window.xmax - window.xmin);
        double zoom = get_zoom_input();
        window.ymax += zoom * quo;
        window.xmax += zoom;
        drawing_area->queue_draw();
    }

    bool draw(const Cairo::RefPtr<Cairo::Context>& cr) {
        // Configuration for dots to appear when drawn
        cr->set_line_cap(Cairo::LINE_CAP_ROUND);

        // Paints background in white
        cr->set_source_rgb(1, 1, 1);
        cr->paint();

        // Changes color to red
        cr->set_source_rgb(0.8, 0, 0);

        // Draw all shapes
        for (int i = 0; i < shapes.size(); i++) {
            draw_shape(cr, shapes[i]);
        }
        cr->stroke();

        return true;
    }

    std::vector<Shape>& shapes;
    Window& window;

    Gtk::DrawingArea* drawing_area = nullptr;

    Gtk::Entry* input_viewport_move = nullptr;
    Gtk::Entry* input_viewport_zoom = nullptr;

    Gtk::Button* button_up = nullptr;
    Gtk::Button* button_down = nullptr;
    Gtk::Button* button_left = nullptr;
    Gtk::Button* button_right = nullptr;
    Gtk::Button* button_in = nullptr;
    Gtk::Button* button_out = nullptr;

protected:
    void draw_shape(const Cairo::RefPtr<Cairo::Context>& cr, Shape& shape) {
        int total_points = shape.points_real.size();

        // First point
        Point first_point = vp_transform(shape.points_real[0]);
        double fx = first_point[0];
        double fy = first_point[1];
        cr->move_to(fx, fy);

        // Lines to other points
        for (Point& point : shape.points_real) {
            Point n = vp_transform(point);
            cr->line_to(n[0], n[1]);
        }

        // Line from last point to first point
        cr->line_to(fx, fy);
    }

    Point vp_transform(Point& p) {
        Gtk::Allocation alloc = drawing_area->get_allocation();
        double xvmax = alloc.get_width();
        double yvmax = alloc.get_height();

        double x = ((p[0] - window.xmin) / (window.xmax - window.xmin)) * (xvmax);
        double y = (1 - ((p[1] - window.ymin) / (window.ymax - window.ymin))) * (yvmax);
        return Point(x, y);
    }

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
    }

    void connect_draw() {
        drawing_area
            ->signal_draw()
            .connect(sigc::mem_fun(*this, &Control::Viewport::draw));
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
};

}  // namespace Control


#endif  // CONTROL_VIEWPORT_H
